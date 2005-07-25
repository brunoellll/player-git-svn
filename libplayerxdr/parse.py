#!/usr/bin/env python

# TODO:
#  - Handle variable-length arrays (I keep getting segfaults)
#
#  - Handle multi-dimensional arrays (e.g., player_sonar_geom_t::poses)


import re
import string
import sys

USAGE = 'USAGE: parse.y <player.h> <pack.c> <pack.h>'

if __name__ == '__main__':

  if len(sys.argv) != 4:
    print USAGE
    sys.exit(-1)

  infilename = sys.argv[1]
  sourcefilename = sys.argv[2]
  headerfilename = sys.argv[3]

  # Read in the entire file
  infile = open(infilename, 'r')
  instream = infile.read()
  infile.close()

  sourcefile = open(sourcefilename, 'w+')
  headerfile = open(headerfilename, 'w+')

  # strip C++-style comments
  pattern = re.compile('//.*')
  instream = pattern.sub('', instream)

  # strip C-style comments
  pattern = re.compile('/\*.*?\*/', re.MULTILINE | re.DOTALL)
  instream = pattern.sub('', instream)

  # strip blank lines        
  pattern = re.compile('^\s*?\n', re.MULTILINE)
  instream = pattern.sub('', instream)

  # find structs
  pattern = re.compile('typedef\s+struct\s+player_\w+[^}]+\}[^;]+',
                   re.MULTILINE)
  structs = pattern.findall(instream)
 
  print 'Found ' + `len(structs)` + ' struct(s)'

  headerfile.write(
'''/*
 * libplayerxdr
 *
 * This library provides functions for translating between player C message
 * structs and their XDR representations.  For each 'struct player_foo',
 * there is a single function of the following name and form:
 *    int player_foo_pack(void* buf, size_t buflen, player_foo_t* msg, int op);
 * This function will either pack (encode to XDR) or unpack (decode from
 * XDR), depending on the last argument.
 *
 * Params:
 *  - buf: The XDR-encoded buffer that is being encoded / decoded.
 *  - buflen: Size of buf, in bytes.
 *  - msg: Pointer to the C struct that is being encoded / decoded.
 *  - op: Either PLAYERXDR_ENCODE or PLAYERXDR_DECODE
 *
 * Returns: On success, the length of the XDR-encoded buffer, and -1
 *          otherwise (e.g., the buffer was not large enough).
 *
 * The caller is responsible for allocating enough space to buf.
 */\n\n''')
  headerfile.write('#ifndef _PLAYERXDR_PACK_H_\n')
  headerfile.write('#define _PLAYERXDR_PACK_H_\n\n')
  headerfile.write('#include <rpc/types.h>\n')
  headerfile.write('#include <rpc/xdr.h>\n\n')
  headerfile.write('#include <libplayercore/player.h>\n\n')
  headerfile.write('#ifdef __cplusplus\nextern "C" {\n#endif\n\n')
  headerfile.write('#define PLAYERXDR_ENCODE XDR_ENCODE\n')
  headerfile.write('#define PLAYERXDR_DECODE XDR_DECODE\n\n')

  sourcefile.write('#include <' + headerfilename + '>\n\n')

  contentspattern = re.compile('.*\{\s*(.*?)\s*\}', re.MULTILINE | re.DOTALL)
  declpattern = re.compile('\s*([^;]*?;)', re.MULTILINE)
  typepattern = re.compile('\s*\S+')
  variablepattern = re.compile('\s*([^,;]+?)\s*[,;]')
  #arraypattern = re.compile('\[\s*(\w*?)\s*\]')
  arraypattern = re.compile('\[(.*?)\]')

  for s in structs:
    # extract prefix for packing function name and type of struct
    split = string.split(s)
    prefix = split[2]
    typename = split[-1]

    # pick out the contents of the struct
    varpart = contentspattern.findall(s)
    if len(varpart) != 1:
      print 'skipping nested / empty struct ' + typename
      continue

    # First time through this loop, we write an xdr_ function for the
    # struct; this function will be used internally if the struct appears
    # inside another struct.
    #
    # Second time through, we write a _pack function for external use.
    for i in range(0,2):

      if i == 0:
        headerfile.write('int xdr_' + typename + '(XDR* xdrs, ' + typename + 
                         '* msg);\n')
        sourcefile.write('int\nxdr_' + typename + '(XDR* xdrs, ' + typename + 
                         '* msg)\n{\n')
      else:
        headerfile.write('int ' + prefix + '_pack(void* buf, size_t buflen, ' +
                         typename + '* msg, int op);\n')
        sourcefile.write('int\n' + prefix + '_pack(void* buf, size_t buflen, ' +
                         typename + '* msg, int op)\n{\n')
        sourcefile.write('  XDR xdrs;\n')
        sourcefile.write('  int len;\n')
        sourcefile.write('  xdrmem_create(&xdrs, buf, buflen, op);\n')
  
      # separate the variable declarations
      decls = declpattern.finditer(varpart[0])
      for d in decls:
        # find the type and variable names in this declaration
        dstring = d.string[d.start(1):d.end(1)]
        type = typepattern.findall(dstring)[0]
        dstring = typepattern.sub('', dstring, 1)
        vars = variablepattern.finditer(dstring)
  
        if type == 'int64_t':
          xdr_proc = 'xdr_long'
        elif type == 'uint64_t':
          xdr_proc = 'xdr_u_long'
        elif type == 'int32_t':
          xdr_proc = 'xdr_int'
        elif type == 'uint32_t':
          xdr_proc = 'xdr_u_int'
        elif type == 'int16_t':
          xdr_proc = 'xdr_short'
        elif type == 'uint16_t':
          xdr_proc = 'xdr_u_short'
        elif type == 'int8_t' or type == 'char':
          xdr_proc = 'xdr_char'
        elif type == 'uint8_t':
          xdr_proc = 'xdr_u_char'
        else:
          # rely on a previous declaration of an xdr_ proc for this type
          xdr_proc = 'xdr_' + type
  
        # iterate through each variable
        for var in vars:
          varstring = var.string[var.start(1):var.end(1)]
          # is it an array or a scalar?
          arraysize = arraypattern.findall(varstring)
          if len(arraysize) > 0:
            arraysize = arraysize[0]
            varstring = arraypattern.sub('', varstring)
            if i == 0:
              sourcefile.write('  if(xdr_vector(xdrs, (char*)&msg->' + 
                               varstring + ', ' + arraysize + 
                               ', sizeof(' + type + '), (xdrproc_t)' + 
                               xdr_proc + ') != 1)\n    return(0);\n')
            else:
              sourcefile.write('  if(xdr_vector(&xdrs, (char*)&msg->' + 
                               varstring + ', ' + arraysize + 
                               ', sizeof(' + type + '), (xdrproc_t)' + 
                               xdr_proc + ') != 1)\n    return(-1);\n')
          else:
            if i == 0:
              sourcefile.write('  if(' + xdr_proc + '(xdrs,&msg->' + 
                               varstring + ') != 1)\n    return(0);\n')
            else:
              sourcefile.write('  if(' + xdr_proc + '(&xdrs,&msg->' + 
                               varstring + ') != 1)\n    return(-1);\n')

      if i == 0:
        sourcefile.write('  return(1);\n}\n\n')
      else:
        sourcefile.write('  len = xdr_getpos(&xdrs);;\n')
        sourcefile.write('  xdr_destroy(&xdrs);\n')
        sourcefile.write('  return(len);\n}\n\n')

  headerfile.write('\n#ifdef __cplusplus\n}\n#endif\n\n')
  headerfile.write('#endif\n')

  sourcefile.close()
  headerfile.close()

