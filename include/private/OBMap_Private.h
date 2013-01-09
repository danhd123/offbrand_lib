/**
 * @file OBMap_Private.h
 * @brief OBMap Private Interface
 * @author theck
 */

#ifndef OBMAP_PRIVATE_H
#define OBMAP_PRIVATE_H

#include "../OBMap.h"

/* DATA */

/**
 * @brief OBMap internal structure, encapsulating all data needed for
 * an instance of OBMap
 */
struct OBMap_struct{
  obj base; /**< obj containing reference count and class membership data */
  /* Additional private data added here, MUST COME AFTER THE obj */
};


/* PRIVATE METHODS */

/**
 * @brief Default constructor for OBMap
 * @return An instance of class OBMap
 * @warning All public constructors should call this constructor and intialize
 * individual members as needed, so that all base data is initialized properly.
 */
OBMap * createDefaultOBMap(void);

/**
 * @brief Hash function for OBMap
 * @param to_hash An obj pointer to an instance of OBMap
 * @return Key value (hash) for the given obj pointer to a OBMap
 */
obhash_t hashOBMap(const obj *to_hash);

/**
 * @brief Compares two instances of OBMap
 *
 * @param a A non-NULL obj pointer to type OBMap
 * @param b A non-NULL obj pointer to type OBMap
 *
 * @retval OB_LESS_THAN obj a is less than b
 * @retval OB_GREATER_THAN obj a is equivalent to b
 * @retval OB_EQUAL_TO obj a is greater than b
 */
int8_t compareOBMaps(const obj *a, const obj *b);
/* Arguments are obj * so that a function pointer can be used for container
 * class sorting/search */

/** 
 * @brief Destructor for OBMap
 * @param to_dealloc An obj pointer to an instance of OBMap with
 * reference count of 0
 * @warning Do not call manually, release will call automatically when the
 * instances reference count drops to 0!
 */
void deallocOBMap(obj *to_dealloc);

/* ADDITIONAL PRIVATE METHOD DECLARATIONS HERE*/

#endif

