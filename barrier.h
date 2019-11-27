#ifndef BARRIER_H_
#define BARRIER_H_

/* The Barrier structure is an example of how encapsulation is
 * often implemented in C.  This header defines a Barrier as a
 * pointer to type struct Barrier, but does not define the struct
 * in this file.  It is valid in C to declare a pointer to a structure
 * for which there is no definition _as long as you never dereference
 * the pointer_.  The pointer then becomes what is called an opaque
 * type; the code using the pointer knows that there is some data stored
 * there, but cannot access it.
 *
 * The implementation file contains a definition for the struct, and can
 * therefore access its contents.
 *
 * This is sometimes accomplished by using the type void *, but the
 * technique used here is more type safe.
 */

typedef struct Barrier *Barrier;

void barrier_wait();

#endif /* BARRIER_H_ */
