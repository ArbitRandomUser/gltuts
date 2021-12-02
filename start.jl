using ModernGL
##cell2
function ModernGL.getprocaddress(name::ASCIIString)
  glutGetProcAddress(name)
end
##
