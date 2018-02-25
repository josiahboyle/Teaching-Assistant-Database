#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ta-list.h"

void init(TA_list *const ta_list_ptr) {

  if(ta_list_ptr != NULL) {
    
    ta_list_ptr -> tas = malloc(sizeof(TA));
  
    ta_list_ptr -> num_ta = 0;

    ta_list_ptr -> next_id = 1;
  }
}

int hire_TA(TA_list *const ta_list_ptr, const char *const first_name,
            const char *const last_name) {

  int i, is_valid = 1, l = 0;

  if(ta_list_ptr != NULL && first_name != NULL && last_name != NULL) {

    i = ta_list_ptr -> num_ta;
  
    while(l < i && is_valid != 0) {

      ta_list_ptr -> tas += l;

      if(strcmp(ta_list_ptr -> tas -> first_name, first_name) == 0 && strcmp(ta_list_ptr -> tas -> last_name, last_name) == 0)
	is_valid = 0;
    
      ta_list_ptr -> tas -= l;
      l++;
    }

    if(is_valid != 0) {
  
      ta_list_ptr -> num_ta += 1;
      ta_list_ptr -> tas = realloc(ta_list_ptr -> tas, sizeof(TA) * (i+1));
      ta_list_ptr -> tas += i;
      ta_list_ptr -> tas -> first_name = malloc(strlen(first_name)+1);
      ta_list_ptr -> tas -> last_name = malloc(strlen(last_name)+1);
      ta_list_ptr -> tas -> id = ta_list_ptr -> next_id;
      strcpy(ta_list_ptr -> tas -> first_name, first_name);
      strcpy(ta_list_ptr -> tas -> last_name, last_name);
      ta_list_ptr -> tas -> salary = 0;
      ta_list_ptr -> next_id += 1;
  
      ta_list_ptr -> tas -= i;
    }
  }
  else
    is_valid = 0;

  return is_valid;
}

int num_TAs(TA_list ta_list) {

  return ta_list.num_ta;
}

int lookup_TA(TA_list ta_list, const char *const first_name,
              const char *const last_name, int *const id) {

  int is_valid = 0, i = 0;
  
  if(last_name == NULL || id == NULL) {

    is_valid = 0;
  }
  else if(first_name == NULL) {

    for(i = 0; i < ta_list.num_ta; i++) {

      ta_list.tas += i;

      if(strcmp(ta_list.tas -> last_name, last_name) == 0) {

	is_valid++;
      }
      
      ta_list.tas -= i;
    }
  }
  else {

    while(i < ta_list.num_ta && is_valid != 1) {

      ta_list.tas += i;

      if(strcmp(ta_list.tas -> last_name, last_name) == 0 && strcmp(ta_list.tas -> first_name, first_name) == 0) {

	*id = ta_list.tas -> id;
	is_valid = 1;
      }
      
      ta_list.tas -= i;
      i++;
    }

    if(is_valid != 1)
      is_valid = -1;
  }

  return is_valid;
}

int set_salary(TA_list ta_list, int id, double salary) {

  int is_valid = 0, i = 0;

  if(salary < 0)
    is_valid = 0;
  
  else {
    
    while(i < ta_list.num_ta && is_valid != 1) {

      ta_list.tas += i;

      if(id == ta_list.tas -> id) {
        
	ta_list.tas -> salary = salary;
	is_valid = 1;
      }
      
      ta_list.tas -= i;
      i++;
    }
  }

  return is_valid;
}

double get_salary(TA_list ta_list, int id) {

  int i = 0;
  double amount = 0;

  while(i < ta_list.num_ta) {

    ta_list.tas += i;

    if(id == ta_list.tas -> id) {

      amount = ta_list.tas -> salary;
    }
      
    ta_list.tas -= i;
    i++;
  }

  return amount;
}

int fire_TA(TA_list *const ta_list_ptr, int id) {

  int is_valid = 0, i = 0;
  TA *temp;

  if(ta_list_ptr != NULL) {
  
    ta_list_ptr -> tas += (ta_list_ptr -> num_ta - 1);
    temp = ta_list_ptr -> tas;
    ta_list_ptr -> tas -= (ta_list_ptr -> num_ta - 1);

    while(i < ta_list_ptr -> num_ta && is_valid != 1) {

      ta_list_ptr -> tas += i;

      if(id == ta_list_ptr -> tas -> id) {

	ta_list_ptr -> tas -> first_name = realloc(ta_list_ptr -> tas -> first_name, strlen(temp -> first_name) + 1);
	ta_list_ptr -> tas -> last_name = realloc(ta_list_ptr -> tas -> last_name, strlen(temp -> last_name) + 1);
	strcpy(ta_list_ptr -> tas -> first_name, temp -> first_name);
	strcpy(ta_list_ptr -> tas -> last_name, temp -> last_name);
	ta_list_ptr -> tas -> salary = temp -> salary;
	ta_list_ptr -> tas -> id = temp -> id;
	is_valid = 1;

	ta_list_ptr -> tas += (ta_list_ptr -> num_ta - i - 1);

	free(ta_list_ptr -> tas -> first_name);
	ta_list_ptr -> tas -> first_name = NULL;
	free(ta_list_ptr -> tas -> last_name);
	ta_list_ptr -> tas -> last_name = NULL;
	ta_list_ptr -> tas -> salary = 0;
	ta_list_ptr -> tas -> id = 0;
      
	ta_list_ptr -> tas -= (ta_list_ptr -> num_ta - i - 1);

	ta_list_ptr -> num_ta -= 1;
      
      }
      
      ta_list_ptr -> tas -= i;
      i++;

      if(is_valid == 1)
	ta_list_ptr -> tas = realloc(ta_list_ptr -> tas, sizeof(TA) * ta_list_ptr -> num_ta);
    }
  }

  return is_valid;
}

void reset(TA_list *const ta_list_ptr) {

  int i;

  if(ta_list_ptr != NULL) {
  
  ta_list_ptr -> tas += ta_list_ptr -> num_ta;
  
  for(i = 0; i < ta_list_ptr -> num_ta; i++) {

    ta_list_ptr -> tas -= 1;
    
    free(ta_list_ptr -> tas -> first_name);
    ta_list_ptr -> tas -> first_name = NULL;
    free(ta_list_ptr -> tas -> last_name);
    ta_list_ptr -> tas -> last_name = NULL;
    ta_list_ptr -> tas -> salary = 0;
    ta_list_ptr -> tas -> id = 0;
  }

  free(ta_list_ptr -> tas);
  ta_list_ptr -> tas = NULL;
  ta_list_ptr -> num_ta = 0;
  
  }
}
