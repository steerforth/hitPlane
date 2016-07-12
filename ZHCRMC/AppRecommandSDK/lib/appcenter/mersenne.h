/*************************** RANDOMC.H ***************** 2007-09-22 Agner Fog *
*
* This file contains class declarations and other definitions for the C++ 
* library of uniform random number generators.
*
* Overview of classes:
* ====================
*
* class CRandomMersenne:
* Random number generator of type Mersenne twister.
* Source file mersenne.cpp
*
* class CRandomMother:
* Random number generator of type Mother-of-All (Multiply with carry).
* Source file mother.cpp
*
*
* Member functions (methods):
* ===========================
*
* All these classes have identical member functions:
*
* Constructor(uint32 seed):
* The seed can be any integer. Usually the time is used as seed.
* Executing a program twice with the same seed will give the same sequence of
* random numbers. A different seed will give a different sequence.
*
* void RandomInit(uint32 seed);
* Re-initializes the random number generator with a new seed.
*
* void RandomInitByArray(uint32 seeds[], int length);
* In CRandomMersenne only: Use this function if you want to initialize with
* a seed with more than 32 bits. All bits in the seeds[] array will influence
* the sequence of random numbers generated. length is the number of entries
* in the seeds[] array.
*
* double Random();
* Gives a floating point random number in the interval 0 <= x < 1.
* The resolution is 32 bits in CRandomMother and CRandomMersenne.
*
* int IRandom(int min, int max);
* Gives an integer random number in the interval min <= x <= max.
* (max-min < MAXINT).
* The precision is 2^-32 (defined as the difference in frequency between 
* possible output values). The frequencies are exact if max-min+1 is a
* power of 2.
*
* int IRandomX(int min, int max);
* Same as IRandom, but exact. In CRandomMersenne only.
* The frequencies of all output values are exactly the same for an 
* infinitely long sequence. (Only relevant for extremely long sequences).
*
* uint32 BRandom();
* Gives 32 random bits. 
*
*
* Example:
* ========
* The file EX-RAN.CPP contains an example of how to generate random numbers.
*
*
* Optimized version:
* ==================
* Faster versions of these random number generators are provided as function
* libraries in asmlib.zip. These function libraries are coded in assembly
* language and support only x86 platforms, including 32-bit and 64-bit
* Windows, Linux, BSD, Mac OS-X (Intel based). Use asmlibran.h from asmlib.zip
*
*
* Non-uniform random number generators:
* =====================================
* Random number generators with various non-uniform distributions are available
* in stocc.zip (www.agner.org/random).
*
*
* Further documentation:
* ======================
* The file randomc.htm contains further documentation on these random number
* generators.
*
*
* Copyright:
============
* � 1997 - 2007 Agner Fog. All software in this library is published under the
* GNU General Public License with the further restriction that it cannot be 
* used for gambling applications. See licence.htm
*******************************************************************************/

#ifndef __MYRANDOM_INC_RANDOM_H__
#define __MYRANDOM_INC_RANDOM_H__

/***********************************************************************
System-specific user interface functions
***********************************************************************/

void EndOfProgram(void);               // System-specific exit code (userintf.cpp)

void FatalError(char * ErrorText);     // System-specific error reporting (userintf.cpp)


/***********************************************************************
Define random number generator classes
***********************************************************************/

class CRandomMersenne {                // Encapsulate random number generator
#if 0
   // Define constants for type MT11213A:
#define MERS_N   351
#define MERS_M   175
#define MERS_R   19
#define MERS_U   11
#define MERS_S   7
#define MERS_T   15
#define MERS_L   17
#define MERS_A   0xE4BD75F5
#define MERS_B   0x655E5280
#define MERS_C   0xFFD58000
#else    
   // or constants for type MT19937:
#define MERS_N   624
#define MERS_M   397
#define MERS_R   31
#define MERS_U   11
#define MERS_S   7
#define MERS_T   15
#define MERS_L   18
#define MERS_A   0x9908B0DF
#define MERS_B   0x9D2C5680
#define MERS_C   0xEFC60000
#endif
public:
   CRandomMersenne(unsigned int seed) {      // Constructor
      RandomInit(seed); LastInterval = 0;}
   void RandomInit(unsigned int seed);       // Re-seed
   void RandomInitByArray(unsigned int seeds[], int length); // Seed by more than 32 bits
   int IRandom (int min, int max);     // Output random integer
   int IRandomX(int min, int max);     // Output random integer, exact
   double Random();                    // Output random float
   unsigned int BRandom();                   // Output random bits
private:
   void Init0(unsigned int seed);            // Basic initialization procedure
   unsigned int mt[MERS_N];                  // State vector
   int mti;                            // Index into mt
   unsigned int LastInterval;                // Last interval length for IRandomX
   unsigned int RLimit;                      // Rejection limit used by IRandomX
   enum TArch {LITTLE_ENDIAN1, BIG_ENDIAN1, NONIEEE}; // Definition of architecture
   TArch Architecture;                 // Conversion to float depends on architecture
};    


class CRandomMother {             // Encapsulate random number generator
public:
   void RandomInit(unsigned int seed);       // Initialization
   int IRandom(int min, int max);      // Get integer random number in desired interval
   double Random();                    // Get floating point random number
   unsigned int BRandom();                   // Output random bits
   CRandomMother(unsigned int seed) {   // Constructor
      RandomInit(seed);}
protected:
   unsigned int x[5];                        // History buffer
};

#endif