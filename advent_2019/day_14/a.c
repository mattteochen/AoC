#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define dim 200

typedef struct node{
	char name[dim];
	int ore;
	int value;
	int tot;
	struct node *n;
} O;

typedef struct excess_reagent{
	char name[dim];
	int quantity;
	struct excess_reagent *n;
} E;

typedef struct created_reagent{
	char name[dim];
	int quantity;
	struct created_reagent *n;
} C;

int result = 0;
C *created_excess_head = NULL, *created_excess_tail = NULL;

void add(O *head, char name[], int q);
void add_remain(C *head_remain, O *head);
void insert_created_excess(C **head, C **tail, char test[], int q);
int search_created(C **head, char test[]);
int search_excess(E **head, char *test);
void insert_excess(E **head, E **tail, char *test,  int q);
void fill_test(char *test, char *row, int pos, int);
void fill_fuel(int *q, char **f_list, char *fuel, int row, char **total, int *);
int count(int size, char **list, char *test, int row, O**, E**, E**);
void ore_counter(char **list, int row, O **head);
void insert_list(O **head, int ore, int val, char add[]);
void add_value(int q, char *test, O **head);

int main(){
	E *excess_head = NULL, *excess_tail = NULL;
	O *head = NULL;
	FILE *f = fopen ("i.txt", "r");
	int row = 0;
	char s[dim];
	fgets(s, dim, f);
	row++;
	while (!feof(f)){
		fgets(s, dim, f);
		row++;
	}
	fclose(f);
	f = fopen ("i.txt", "r");
	char **list = (char**)malloc(sizeof(char*)*row);
	for (int i=0; i<row; i++){
		list[i] = (char*)malloc(sizeof(char)*dim);
		fgets(list[i], dim, f);
		printf ("%s", list[i]);
	}
	printf ("\n\n");
	fclose(f);
	printf ("row:%d\n", row);	
	ore_counter(list, row, &head);
	O *c = head;
	printf ("list complete\n");
	while (c != NULL){
		printf ("List: %s - %d - %d\n", c->name, c->ore, c->value);
		c = c->n;
	}

	//find the fuel row:
	char fuel[dim] = "FUEL";
	char **f_list = (char**)malloc(sizeof(char*)*20);
	int quantity[20];
	for (int i=0; i<20; i++){
		quantity[i] = -1;
		f_list[i] = (char*)malloc(sizeof(char)*dim);
	}	
	int d = 0;
	fill_fuel(quantity, f_list, fuel, row, list, &d);
	
	int res = 0;
	for (int i=0; i<20; i++){
		if (quantity[i] == -1)
			break;
		if (strlen(f_list[i]) < 1)
			break;
		res += count(quantity[i], list, f_list[i], row, &head, &excess_head, &excess_tail);
	}

	//print excess reagents
	E *t = excess_head;
	printf ("check excess:\n\n");
	while (t != NULL){
		printf ("%s - %d\n", t->name, t->quantity);
		t = t->n;
	}
	printf ("\nend check\n\n");

	//add_remain(created_excess_head, head);
	c = head;
	long re = 0;
	while (c != NULL){
		printf ("this tot: %d\n", c->tot);
		int t = 0;
		int r = 0;
		if (c->tot != 0){
			while (t < c->tot){
				t += c->value;
				r += c->ore;
			}
		}
		printf ("r: %d\n", r);
		re += r;
		c = c->n;
	}
	printf ("res: %ld\n", re);
	
	for (int i=0; i<20; i++)
		free(f_list[i]);
	for (int i=0; i<row; i++)
		free(list[i]);
	free(list);
	free(f_list);
	c = head;
	O *p = NULL;
	while (c != NULL){
		if (p != NULL)
			free(p);
		p = c;
		c = c->n;
	}
	free(p);
	E *cc = excess_head;
	E *pp = NULL;
	while (cc != NULL){
		if (pp != NULL)
			free(pp);
		pp = cc;
		cc = cc->n;
	}
	free(pp);
	C *ccc = created_excess_head;
	C *ppp = NULL;
	while (ccc != NULL){
		if (ppp != NULL)
			free(ppp);
		ppp = ccc;
		ccc = ccc->n;
	}
	free(ppp);

	return 0;
}

void add(O *head, char name[], int q){
	O *c = head;

	while (c != NULL){
		if (strcmp(c->name, name) == 0){
			printf ("ADDING - %s - %d\n", c->name, q);
			c->tot += q;
			break;
		}
		c = c->n;
	}
}

void add_remain(C *head_remain, O *head){
	O *c = head;
	C *cr = head_remain;

	while (cr != NULL){
		if (cr->quantity != 0){
			add(head, cr->name,  cr->quantity);
		}
		cr = cr->n;
	}
}

void insert_list(O **head, int ore, int val, char add[]){
	O *new = (struct node*)malloc(sizeof(struct node));
	new->ore = ore;
	new->value = val;
	strcpy(new->name, add);
	new->n = NULL;
	new->tot = 0;

	O *c = *head;

	if (c == NULL)
		*head = new;
	else{
		while (c->n != NULL)
			c = c->n;
		c->n = new;
	}
}

void ore_counter(char **list, int row, O **head){
	char o[4] = "ORE";
	char test[4];
	test[3] = '\0';
	int c = 0;
	int n1 = 0, n2 = 0;
	for (int i=0; i<row; i++){
		n1 = atoi(list[i]);
		for (int j=0; j<strlen(list[i])-3; j++){
			fill_test(test, list[i], j, 3);
			if (strcmp(test, o) == 0){
				int p = 0;
				while (list[i][p] != '>')
					p++;
				p += 2;
				n2 = atoi(&list[i][p]);
				while (list[i][p] != ' ')
					p++;
				p++;
				char to_insert[dim];
				int ic = 0, k = p;
				while (list[i][k] >= 65 && list[i][k] <= 90){
					to_insert[ic] = list[i][k];
					k++;
					ic++;
				}	
				to_insert[ic] = '\0';
				insert_list(head, n1, n2, to_insert);
				break;
			}
		}	
	}
}

void insert_created_excess(C **head, C **tail, char test[], int q){
	C *new = (C*)malloc(sizeof(C));
	if (new == NULL)
		return;
	new->quantity = q;
	strcpy(new->name, test);
	new->n = NULL;

	if (*head == NULL){
		*head = new;
		*tail = new;
	}
	else{
		(*tail)->n = new;
		*tail = new;
	}
}

int search_created(C **head, char test[]){
	C *c = *head, *p = NULL;
	while (c != NULL){
		if (strcmp(c->name, test) == 0){
			int ret = c->quantity;
			if (c == *head){
				*head = c->n;
				free(c);
			}
			else{
				p->n = c->n;
				free(c);
			}
			return ret;
		}
		p = c;
		c = c->n;
	}
	return 0;
}

void add_value(int q, char *test, O **head){
	O *c = *head;
	while (c != NULL){
		if (strcmp((c->name), test) == 0){
			//check if are there previous created excess
			/*
			int prev_excess = search_created(&created_excess_head, c->name);
			if (prev_excess != 0)
				q -= prev_excess;
			if (q > c->value){
				int i = 0;
				while (i < q){
					i += c->value;
				}
				if (i > q){
					printf ("INSERT BASE CASE: %d\n", i-q);
					insert_created_excess(&created_excess_head, &created_excess_tail, c->name, i-q);
				}
			}
			*/
			printf ("adding: %d\n", q);
			c->tot += q;
			break;
		}
		c = c->n;
	}
}

void insert_excess(E **head, E **tail, char *test,  int q){
	E *new = (E*)malloc(sizeof(E));
	if (new == NULL)
		return;
	strcpy(new->name, test);
	new->quantity = q;
	new->n = NULL;
	
	//check if is there arleady the same reagent
	E *c = *head;
	while (c != NULL){
		if (strcmp(c->name, test) == 0){
			c->quantity += q;
			return;
		}
		c = c->n;
	}

	if (*head == NULL){
		*head = new;
		*tail = new;
	}
	else{
		(*tail)->n = new;
		*tail = new;
	}
}

int search_excess(E **head, char *test){
	E *c = *head, *p = NULL;
	while (c != NULL){
		if (strcmp(c->name, test) == 0){
			int ret = c->quantity;
			if (c == *head){
				*head = c->n;
				free(c);
			}
			else{
				p->n = c->n;
				free(c);
			}
			return ret;
		}
		p = c;
		c = c->n;
	}
	return 0;
}

int count(int size, char **list, char *test, int row, O **head, E **excess_head, E **excess_tail){	
	//hipotetically 20 is the max number of reagents for one reaction
	
	char **newlist = (char**)malloc(sizeof(char*)*20);
	int *newq = (int*)malloc(sizeof(int)*20), res = 0;

	for (int i=0; i<20; i++){
		newlist[i] = (char*)malloc(sizeof(char)*dim);
	}
	for (int k=0; k<20; k++)
		newq[k] = -1;
	
	int d = 0;
	fill_fuel(newq, newlist, test, row, list, &d);
	
	if (d < size){
		//search if are there previuos excess reagents
		int previous_excess = search_excess(excess_head, test);
		printf ("EXCESS: %d\n", previous_excess);
		if (previous_excess != 0)
			size -= previous_excess;
		int mult = size/d;
		int d_copy = d;
		if (size%d != 0)
			mult++;
		d *= mult;
		//if we produce excess reagent we save it for later (only if size%d != 0)
		if (size%d_copy != 0 && strcmp(newlist[0], "ORE") != 0){
			printf ("\n\nEX: %s - %d\n%d %d\n\n", test, d-size, d, size);
			insert_excess(excess_head, excess_tail, test, d-size);
		}
		for (int i=0; i<20; i++)
			newq[i] *= mult;
	}
	else if (d > size){
		int previous_excess = search_excess(excess_head, test);
		printf ("EXCESS: %d\n", previous_excess);
		if (previous_excess != 0)
			size -= previous_excess;

		insert_excess(excess_head, excess_tail, test, d-size);
	}

	if (strcmp(newlist[0], "ORE") == 0){
		add_value(size, test, head);
		return 0;
	}
	else{
		for (int i=0; i<20; i++){
			if (strlen(newlist[i]) < 1)
				break;			
			res += count(newq[i], list, newlist[i], row, head, excess_head, excess_tail);
		}
	}

	for (int i=0; i<20; i++)
		free(newlist[i]);
	free(newlist);
	free(newq);
	return res;
}
	
void fill_fuel(int *quantity, char **f_list, char *fuel, int row, char **total, int *divisor){
	printf ("tosearch: %s\n", fuel);	
	char *test = (char*)malloc(sizeof(char)*strlen(fuel)+1);
	test[strlen(fuel)] = '\0';
	int fuel_row = -1;
	for (int i=0; i<row; i++){
		int p = 0;
		while (total[i][p] != '>')
			p++;
		p += 2;
		int n = atoi(&total[i][p]);
		for (int k=p; k<strlen(total[i]); k++){
			fill_test(test, total[i], k, strlen(fuel));
			if (strcmp(test, fuel) == 0){
				fuel_row = i;
				*divisor = n;
			}
		}
	}
	int qc = 0, lc = 0, i = 0;
	printf ("this row: %s\n", total[fuel_row]);
	while (i < strlen(total[fuel_row])){
		if (total[fuel_row][i] >= 48 && total[fuel_row][i] <= 57){
			quantity[qc] = atoi(&total[fuel_row][i]);
			qc++;
			
			while (total[fuel_row][i] != ' ')
				i++;
			i++;
			int counter = 0;
			while (total[fuel_row][i] != ' ' && total[fuel_row][i] != ','){
				f_list[lc][counter] = total[fuel_row][i];
				counter++;
				i++;
			}
			f_list[lc][counter] = '\0';
			printf ("%s\n", f_list[lc]);
			lc++;
		}
		else
			i++;
		if (total[fuel_row][i] == '=')
			break;
	}
	free(test);
}

void fill_test(char *test, char *row, int pos, int lenght){
	int i = 0;
	for (i=0; i<lenght; i++, pos++){
		test[i] = row[pos];
	}
	test[i] = '\0';
}
