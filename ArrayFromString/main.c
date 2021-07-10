//
//  main.c
//  ArrayFromString
//
//  Created by Panayotis Matsinopoulos on 10/7/21.
//

#include <stdio.h>
#include <CoreFoundation/CoreFoundation.h>

void applier(const void *value, void *context) {
  CFStringRef s = (CFStringRef)value;
  CFRetain(s);
  
  const char *cp = CFStringGetCStringPtr(s, CFStringGetSystemEncoding());
  
  if (cp) {
    printf("%s\n", cp);
  }
  else {
    CFIndex bufferSize = sizeof(char) * (CFStringGetLength(s) + 1);
    char *buffer = malloc(bufferSize);
    memset(buffer, 0, bufferSize);
    
    CFStringGetCString(s, buffer, bufferSize, CFStringGetSystemEncoding());
    
    printf("%s\n", buffer);
    
    free(buffer);
  }
  
  CFRelease(s);
}

int main(int argc, const char * argv[]) {
  CFStringRef stringToParse = CFSTR("John Pappas,Mary Foo,Peter Pan");
  CFStringRef separatorString = CFSTR(",");
  
  CFArrayRef array = CFStringCreateArrayBySeparatingStrings(kCFAllocatorDefault, stringToParse, separatorString);
  
  CFArrayApplyFunction(array,
                       CFRangeMake((CFIndex)0,
                                   (CFIndex)CFArrayGetCount(array)),
                       applier,
                       NULL);
    
  CFRelease(array);
  
  return 0;
}
