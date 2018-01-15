#ifndef h__ISR_VECTOR_H__
#define h__ISR_VECTOR_H__

/*
 * Include file for interrupt service routines.
 */

/*
 * The interrupt service routines. These link in the function `main` as the
 * main function.
 */
extern const void* isr_vector[];


/*
 * Defines an error state. This loops forever and defines a distinct flashing
 * pattern to let the user know an unhandled ISR happened.
 */
void unhandled_isr();

#endif /* h___ISR_VECTOR_H__ */
