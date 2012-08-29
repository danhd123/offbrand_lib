
#include "../../include/minlog_funct.h"
#include "../../include/NCube.h"
#include "../../include/Term.h"

uint8_t numOneBits(uint32_t num){

  uint8_t i;
  uint8_t bit_count = 0;

  for(i=0; i<32; i++) bit_count += (num >> i)%2;

  return bit_count;
}


OBVector * findLargestPrimeImplicants(const OBVector *terms, 
                                      const OBVector *dont_cares){

  uint32_t i, j, k, maxi, maxj;
  int32_t loop;
  OBVector *result, *cube_vectors, *cur_cube_vector, *prev_cube_vector;
  NCube *tmp_cube, *a, *b;
  Term *tmp_term;

  assert(terms != NULL && sizeOfVector(terms) != 0);

  maxi = sizeOfVector(terms);

  /* create vector for 0 cubes */
  cur_cube_vector = createVector(sizeOfVector(terms)+sizeOfVector(dont_cares));

  /* create all cubes associated with terms */
  for(i=0; i<maxi; i++){
    /* get term for cube creation */
    tmp_term = (Term *)objAtVectorIndex(terms, i);
    assert(objIsOfClass((obj *)tmp_term, "Term"));

    /* create cube from term, which is not a dont care cube */
    tmp_cube = createNCube(getTermValue(tmp_term), 0);

    /* add cube to cur_cube_vector */
    addToVector(cur_cube_vector, (obj *)tmp_cube);

    /* release tmp_cube so only vector maintains valid reference */
    release((obj *)tmp_cube);
  }

  /* if dont_care terms are supplied, create cubes for them */
  if(dont_cares){

    maxi = sizeOfVector(dont_cares);

    for(i=0; i<maxi; i++){
      /* get term for cube creation */
      tmp_term = (Term *)objAtVectorIndex(terms, i);
      assert(objIsOfClass((obj *)tmp_term, "Term"));

      /* create cube from term, which is not a dont care cube */
      tmp_cube = createNCube(getTermValue(tmp_term), 0);

      /* add cube to cur_cube_vector */
      addToVector(cur_cube_vector, (obj *)tmp_cube);

      /* release tmp_cube so only vector maintains valid reference */
      release((obj *)tmp_cube);
    }
  }


  /* create vector to contain vectors of NCubes (each sub vector contains cubes
   * of all the same order) */
  cube_vectors = createVector(1);
  
  /* add 0 cube vector to vector of vectors */
  addToVector(cube_vectors, (obj *)cur_cube_vector);

  /* release cur_cube_vector so only cube_vectors maintains valid reference */
  release((obj *)cur_cube_vector);

  /* while cubes can still be merged into larger cubes */
  k = 0;
  loop = 1;
  while(loop>0){

    /* by default set loop to stop after this run, two cubes of current order
     * must be created to continue search for additional higher order cubes */
    loop = -1; 

    /* get previous cube vector, and create new vector for next order of cubes*/
    prev_cube_vector = (OBVector *)objAtVectorIndex(cube_vectors, k);
    cur_cube_vector = createVector(sizeOfVector(prev_cube_vector)/4);

    /* for all pairs cubes, attempt to merge */
    maxi = sizeOfVector(prev_cube_vector);
    for(i=0; i<maxi-1; i++){

      a = (NCube *)objAtVectorIndex(prev_cube_vector, i);

      for(j=i+1; j<maxi; j++){

        b = (NCube *)objAtVectorIndex(prev_cube_vector, i);
        /*if cubes can be merged */

        if((tmp_cube = mergeNCubes(a, b))){
          addToVector(cur_cube_vector, (obj *)tmp_cube);
          /* release tmp_cube so that vector has only valid reference */
          release((obj *)tmp_cube);
          /* increment loop to indicate that another larger cube was created */
          loop++;
        }
      }
    }
    
    addToVector(cube_vectors, (obj *)cur_cube_vector);
    /* release cur_cube_vector so cube_vectors maintains only valid reference */
    release((obj *)cur_cube_vector);
    /* increment k to work on next order of cube vectors */
    k++;
  }

  /* Create final vector of only prime implicant cubes */
  result = createVector(4);

  maxi = sizeOfVector(cube_vectors);
  for(i=0; i<maxi; i++){
    
    cur_cube_vector = (OBVector *)objAtVectorIndex(cube_vectors, i);
    maxj = sizeOfVector(cur_cube_vector);

    for(j=0; j<maxj; j++){
      tmp_cube = (NCube *)objAtVectorIndex(cur_cube_vector, j);
      if(isNCubePrimeImplicant(tmp_cube)){
        addToVector(result, (obj *)tmp_cube);
      }
    }
  }

  release((obj *)cube_vectors);
  return result;
}
