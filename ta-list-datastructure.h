#if !defined(TA_LIST_DATASTRUCTURE__H)
#define TA_LIST_DATASTRUCTURE__H

typedef struct {
  
  char *first_name;
  char *last_name;
  int id;
  double salary;
  
} TA;

typedef struct {

  TA *tas;
  int num_ta;
  int next_id;
  
} TA_list;

#endif
