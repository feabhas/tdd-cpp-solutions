#ifndef TESTDEFS_H
#define TESTDEFS_H

// Redefine visibility modifiers to
// allow test code to examine the internals
// of our classes, if necessary.
//
#ifdef ACCESS_CLASS_INTERNALS
#define private public
#define protected public
#endif

#endif // TESTDEFS_H