// Header files for standard input/output, dynamic memory allocation, and limits
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

// Structure to represent a node in the adjacency list
struct node {
    int vertex;
    int weight;
    struct node* next;
};

// Structure to represent a path in a circular doubly linked list
struct path {
    struct path* prev;
    int data;
    struct path* next;
};
typedef struct path N;

N* tail = NULL; // Global variable to keep track of the tail of the circular doubly linked list
N* AddtoEmpty(int data); // Function to add a node to an empty circular doubly linked list

N* addToEnd(int ele); // Function to add a node to the end of a circular doubly linked list

void printname_inprintpath(int num); // Function to print the station name corresponding to a given station number

int name_to_num(char name_tobe_found[]); // Function to convert station name to station number

int code_to_num(char code_tobe_found[]); // Function to convert station code to station number

void printPath(int parent[], int s, int v); // Function to print the path from source to destination using station numbers

void printName(int num, int col); // Function to print station information (color, name, code, parking) based on station number and column number

void dijkstra(struct node* adj[], int n, int s, int dist[], int parent[]); // Function to perform Dijkstra's algorithm to find the shortest path in the graph

void addEdge(struct node* adj[], int src, int dest, int weight); // Function to add an edge between two vertices in the graph

void createGraph(struct node* adj[126]); // Function to create the graph with edges representing metro lines

void display_stations(); // Function to display the list of all metro stations with their information

void display_stations_a(); // Function to display the list of all metro stations in alphabetical order

int countNode(); // Function to count the number of nodes in the circular doubly linked list

int encoding(int ele); // Function to encode metro station numbers based on the color of the metro line

void getStn(int a[3]); // Function to display the interchange points between different metro lines

void InterChange(); // Function to identify and print the interchange points between the source and destination

void getCost(); // Function to calculate and print the cost of the metro fare

void freeStations(N* head); // Function to free the memory allocated for the circular doubly linked list

void freeGraph(struct node* adj[], int n); // Function to free the memory allocated for the graph (adjacency list)



// Main function
int main()
{
    int n = 126;
    struct node* adj[n];
    for (int i = 0; i < n; i++) 
	{
        adj[i] = NULL;
    }
    createGraph(adj);
						
	printf("\n------------------------------------------------------------------------------------------\n\n");
	printf("Welcome to Namma Metro Sanchara!\n");
	printf("We will be assisting you to choose the best metro route to reach your destination\n");
	printf("\n------------------------------------------------------------------------------------------\n");		

	int choice=1;
	
	while(choice)
	{
				int o,errr=1;
				int op1, c;
				int er=1;
				while(er)
				{
					printf("Enter :\n1 - to view the list of metro stations\n2 - to enter source and destination\n");
					printf("Your option : ");
					
					scanf("%d", &op1);
					while ((c = getchar()) != '\n' && c != EOF); // Clear the input buffer

					switch (op1)
					{
						case 1:
						
						display_stations();
						er=0;
						while(errr)
						{
							printf("\nEnter 1 to sort in alphabetical order\nEnter 0 otherwise\n");
							printf("Enter : ");
							scanf("%d",&o);
							if(o==1)
							{
								display_stations_a();
								errr=0;
							}
							else if(o==0)
							{
								errr=0;
							}
							else
							{
								errr=1;
								printf("\nERROR, you have entered the wrong option\nPlease re-enter -\n\n");
							}
						}
						break;

						case 2:
							er=0;
							break;

						default:
							er=1;
							printf("\nERROR, you have entered the wrong option\nPlease re-enter -\n\n");
							break;
					}
				}
				
				printf("\n------------------------------------------------------------------------------------------\n");
				
				char src_name[100], des_name[100];
				int source=0, des=0;

				
				int er2=1;
				int er5=1;
				while(er2)
					
				{
					
					printf("Enter :\n1 - to enter full name of station\n2 - to enter station code\n3 - to enter station number\n");
					int op_src;

					scanf("%d", &op_src);
					while ((c = getchar()) != '\n' && c != EOF); // Clear the input buffer
					
					
					
					switch (op_src)
					{
						case 1:
							er2=0;
							while(er5)
							{
								printf("Enter source - ");
								fgets(src_name, sizeof(src_name), stdin); // Use fgets to read strings
								src_name[strcspn(src_name, "\n")] = 0; // Remove the trailing newline
								printf("Enter destination - ");
								fgets(des_name, sizeof(des_name), stdin);
								des_name[strcspn(des_name, "\n")] = 0;
								
								source=name_to_num(src_name);
								des=name_to_num(des_name);
								
								if(source!=999 && des!=999)
									er5=0;
								else 
								{
									printf("\nERROR, you have entered the wrong option\nPlease re-enter -\n\n");
									er5=1;
								}
							}
								
								
							
							break;

						case 2:
							while(er5)
							{
								er2=0;
								printf("Enter source - ");
								fgets(src_name, sizeof(src_name), stdin);
								src_name[strcspn(src_name, "\n")] = 0;
								printf("Enter destination - ");
								fgets(des_name, sizeof(des_name), stdin);
								des_name[strcspn(des_name, "\n")] = 0;
								
								source=code_to_num(src_name);
								des=code_to_num(des_name);
								
								if(source!=999 && des!=999)
									er5=0;
								else
								{
									printf("\nERROR, you have entered the wrong option\nPlease re-enter -\n\n");
									er5=1;
								}
							}
							break;

						case 3:
							while(er5)
							{
								er2=0;
								printf("Enter source - ");
								scanf("%d", &source);
								while ((c = getchar()) != '\n' && c != EOF); // Clear the input buffer
								printf("Enter destination - ");
								scanf("%d", &des);
								while ((c = getchar()) != '\n' && c != EOF); // Clear the input buffer
								if(source>=0 && source<=125 && des>=0 && des<=125)
									er5=0;
								else
								{
									printf("\nERROR, you have entered the wrong option\nPlease re-enter -\n\n");
									er5=1;
								}					
							}
							break;

						default:
							er2=1;
							printf("\nERROR, you have entered the wrong option\nPlease re-enter -\n\n");
							break;
					}
				}
				printf("\n------------------------------------------------------------------------------------------\n");
				
				
				int dist[n];
				int parent[n];

				dijkstra(adj, n, source, dist, parent);
				
				
				printf("\n\n\nHere are your results :\n\n");
				
				printf("1.) Source : "); 
				printName(source,2);
				printf("\n\n");
				
				printf("2.) Destination : ");
				printName(des,2);
				printf("\n");
				
				
				printf("\n3.) Metro Route : \n");
				if (dist[des] == INT_MAX) 
				{
					printf("No path exists between source and destination.\n");
				}
				else 
				{
					printPath(parent, source, des);
				}
				printf("\n");
				
				printf("\n4.) Interchange : "); 
				InterChange();
				printf("\n");
				
				printf("\n5.) Metro fare : Rs."); getCost(); 
				printf("\n");
				
				
				printf("6.) Parking at "); printName(source,2); printf(": ");
				printName(source,4);
				
				printf("7.) Parking at "); printName(des,2); printf(": ");
				printName(des,4);
				
				printf("\n------------------------------------------------------------------------------------------\n");
				
				printf("Do you wish to continue? (enter 0 to exit, enter 1 to continue)\n");
				scanf("%d",&choice);
				

	}
	printf("Thank you for choosing Namma Metro! Exiting...\n");


	freeStations(tail->next);  // Free the linked list of stations
    freeGraph(adj, n);         // Free the adjacency list
	
    return 0;
}

//-----------------------------------------------------------------------
// Data structure used: Adjacency List
// The following functions deal with the creation of the adjacency list:

// Function to add a particular edge into the adjacency list
void addEdge(struct node* adj[], int src, int dest, int weight) 
{
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    newNode->vertex = dest;
    newNode->weight = weight;
    newNode->next = adj[src];
    adj[src] = newNode;

    newNode = (struct node*)malloc(sizeof(struct node));
    newNode->vertex = src;
    newNode->weight = weight;
    newNode->next = adj[dest];
    adj[dest] = newNode;
    // The function ensures two-way connectivity is established: e.g., A->B as well as B->A connectivity established
}

// Using the addEdge(), we create the graph using the station numbers as encoded in the CSV file
void createGraph(struct node* adj[126]) 
{
    for (int i = 0; i < 36; i++) // Purple line
    {
        addEdge(adj, i, i + 1, 2);
    }

    for (int j = 37; j < 51; j++) // Till Chikpet
    {
        addEdge(adj, j, j + 1, 2);
    }

    addEdge(adj, 51, 14, 2);
    addEdge(adj, 52, 14, 2);

    for (int j = 52; j < 67; j++) // Till the end of the Green line
    {
        addEdge(adj, j, j + 1, 2);
    }

    for (int k = 68; k < 82; k++) // Yellow line, fully
    {
        addEdge(adj, k, k + 1, 2);
    }

    addEdge(adj, 82, 45, 2);

    for (int m = 83; m < 85; m++) // Pink line, till JP Nagar 4th stage
    {
        addEdge(adj, m, m + 1, 2);
    }

    addEdge(adj, 86, 81, 2);
    addEdge(adj, 81, 86, 2);

    for (int n = 87; n < 91; n++) // Pink line, till Rashtriya Military School
    {
        addEdge(adj, n, n + 1, 2);
    }

    addEdge(adj, 91, 18, 2);
    addEdge(adj, 92, 18, 2);

    for (int m = 92; m < 98; m++) // Pink line, till JP Nagar 4th stage
    {
        addEdge(adj, m, m + 1, 2);
    }

    for (int m = 99; m < 109; m++) // Blue line, till Mahadevpura
    {
        addEdge(adj, m, m + 1, 2);
    }

    addEdge(adj, 109, 25, 2);
    addEdge(adj, 110, 25, 2);

    for (int m = 110; m < 114; m++) // Blue line, till HBR layout
    {
        addEdge(adj, m, m + 1, 2);
    }

    addEdge(adj, 114, 98, 2);
    addEdge(adj, 115, 98, 2);

    for (int m = 115; m < 125; m++) // Blue line, till HBR layout
    {
        addEdge(adj, m, m + 1, 2);
    }
}

//-----------------------------------------------------------------------
// Data structure used: Circular Doubly Linked List

// Add a node to an empty list
N* AddtoEmpty(int data) 
{
    N* temp = malloc(sizeof(N));
    temp->prev = temp;
    temp->data = data;
    temp->next = temp; // Make next point to itself to form a circular list
    if (tail == NULL) 
    {
        tail = temp; // Set the tail to the first node in the list
    }
    return temp;
}

// Add a node to the end of the list
N* addToEnd(int ele) 
{
    if (tail == NULL) 
    {
        return AddtoEmpty(ele); // If the list is empty, add to the empty list
    }

    N* newp = malloc(sizeof(N));
    newp->data = ele;
    newp->next = tail->next;
    newp->prev = tail;
    tail->next = newp;
    newp->next->prev = newp;
    tail = newp; // Update the tail to the new node
    return newp;
}

// Count the number of nodes in the circular doubly linked list
int countNode()
{
    int c;
    if (tail == NULL)
        return 0;

    N* head = tail->next;

    {
        c = 1;
        struct path* ptr = head;
        while (ptr->next != tail) 
        {
            c++;
            ptr = ptr->next;
        }
    }
    return c;
}

// Calculate and display the cost based on the number of nodes in the circular doubly linked list
void getCost() 
{
    int cnt = countNode();
    int baseCost = cnt * 10;
    int cost = baseCost;
    if (cnt > 15) 
    {
        cost = cost - (int)(0.7 * baseCost); // 70% discount
    }
    else if (cnt > 12) 
    {
        cost = cost - (int)(0.5 * baseCost); // 50% discount
    } 
    else if (cnt > 10) 
    {
        cost = cost - (int)(0.4 * baseCost); // 40% discount
    } 
    else if (cnt > 5) 
    {
        cost = cost - (int)(0.2 * baseCost); // 20% discount
    }

    printf("%d\n", cost);
}

//-----------------------------------------------------------------------

// Function to print the station name when traversing the circular doubly linked list in printPath
void printname_inprintpath(int num) 
{
    addToEnd(num);
    // Note: col 1=Line color, 2=station name, 3=code, 4=parking
    int x;

    FILE* fp = fopen("Metro.csv", "r");

    if (!fp) 
    {
        printf("Can't open file\n");
        return; // Exit the program with an error code
    }

    char line[1000];
    while (fgets(line, sizeof(line), fp) != NULL) 
    {
        char* no = strtok(line, ",");
        char* color = strtok(NULL, ",");
        char* name = strtok(NULL, ",");

        int n = atoi(no);

        if (num == n)
            printf("-> %s ", name);
    }
    fclose(fp);
}

// Print the path using the parent array obtained from Dijkstra's algorithm
void printPath(int parent[], int s, int v) 
{
    if (v == s) 
    {
        printname_inprintpath(v);
        return;
    }
    printPath(parent, s, parent[v]);
    printname_inprintpath(v);
}

//-----------------------------------------------------------------------

// Function to convert station name to station number
int name_to_num(char name_tobe_found[]) 
{
    FILE* fp = fopen("Metro.csv", "r");

    if (!fp) 
    {
        printf("Can't open file\n");
        return -1; // Return an error code
    }

    char line[1000];
    while (fgets(line, sizeof(line), fp) != NULL) 
    {
        char* no = strtok(line, ",");
        char* color = strtok(NULL, ",");
        char* name = strtok(NULL, ",");

        int n = atoi(no);

        if (strcmp(name, name_tobe_found) == 0) 
        {
            fclose(fp);
            return n;
        }
    }
    fclose(fp);
    return 999;
}

// Function to convert station code to station number
int code_to_num(char code_tobe_found[]) 
{
    FILE* fp = fopen("Metro.csv", "r");

    if (!fp) 
    {
        printf("Can't open file\n");
        return -1; // Return an error code
    }

    char line[1000];
    while (fgets(line, sizeof(line), fp) != NULL) 
    {
        char* no = strtok(line, ",");
        char* color = strtok(NULL, ",");
        char* name = strtok(NULL, ",");
        char* code = strtok(NULL, ",");

        int n = atoi(no);

        if (strcmp(code, code_tobe_found) == 0) 
        {
            fclose(fp);
            return n;
        }
    }

    fclose(fp);
    return 999;
}

// Function to print station information based on station number and column
void printName(int num, int col) 
{
    // Note: col 1=Line color, 2=station name, 3=code, 4=parking
    int x;

    FILE* fp = fopen("Metro.csv", "r");

    if (!fp) 
    {
        printf("Can't open file\n");
        return; // Exit the program with an error code
    }

    char line[1000];
    while (fgets(line, sizeof(line), fp) != NULL) 
    {
        char *no = strtok(line, ",");
        char *color = strtok(NULL, ",");
        char *name = strtok(NULL, ",");
        char *code = strtok(NULL, ",");
        char *parking = strtok(NULL, ",");

        int n = atoi(no);

        if (col == 1 && num == n)
            printf("%s", color);
        if (col == 2 && num == n)
            printf("%s ", name);
        if (col == 3 && num == n)
            printf("%s\n", code);
        if (col == 4 && num == n)
            printf("%s\n", parking);
    }

    fclose(fp);
    return;
}

//-----------------------------------------------------------------------

// Dijkstra's algorithm to find the shortest path in the metro graph
void dijkstra(struct node* adj[], int n, int s, int dist[], int parent[]) 
{
    int visited[n];
    for (int i = 0; i < n; i++) 
    {
        dist[i] = INT_MAX;
        visited[i] = 0;
        parent[i] = -1; // Initialize the parent array
    }

    dist[s] = 0;

    for (int count = 0; count < n - 1; count++) 
    {
        int u, min_distance = INT_MAX;

        for (u = 0; u < n; u++) 
        {
            if (!visited[u] && dist[u] < min_distance) 
            {
                min_distance = dist[u];
                s = u;
            }
        }

        visited[s] = 1;

        struct node* current = adj[s];
        while (current != NULL) 
        {
            int v = current->vertex;
            int weight = current->weight;

            if (!visited[v] && dist[s] != INT_MAX && dist[s] + weight < dist[v]) 
            {
                dist[v] = dist[s] + weight;
                parent[v] = s; // Update the parent of vertex v
            }
            current = current->next;
        }
    }
}

//-----------------------------------------------------------------------

// Function to display all stations from the CSV file
void display_stations() 
{
    int x;

    FILE* fp = fopen("Metro.csv", "r");

    if (!fp) 
    {
        printf("Can't open file\n");
        return; // Exit the program with an error code
    }

    char line[1000];
    while (fgets(line, sizeof(line), fp) != NULL) 
    {
        char *no = strtok(line, ",");
        char *color = strtok(NULL, ",");
        char *name = strtok(NULL, ",");
        char *code = strtok(NULL, ",");

        // Check if "src" and "dest" are available in the CSV file
        if (no && name && code) 
        {
            printf("%s %s\t%s\t%s\n", no, name, color, code);
        }
    }

    fclose(fp);
    return;
}

// Function to display all stations from an alternate CSV file
void display_stations_a() 
{
    int x;

    FILE* fp = fopen("Metro_a.csv", "r");

    if (!fp) 
    {
        printf("Can't open file\n");
        return; // Exit the program with an error code
    }

    char line[1000];
    while (fgets(line, sizeof(line), fp) != NULL) 
    {
        char *no = strtok(line, ",");
        char *color = strtok(NULL, ",");
        char *name = strtok(NULL, ",");
        char *code = strtok(NULL, ",");

        // Check if "src" and "dest" are available in the CSV file
        if (no && name && code) 
        {
            printf("%s %s\t%s\t%s\n", no, name, color, code);
        }
    }

    fclose(fp);
    return;
}

//-----------------------------------------------------------------------

// Function to encode station numbers into line numbers
int encoding(int ele)
{
    if (0 <= ele && ele <= 36)
        return 1;
    else if (37 <= ele && ele <= 67)
        return 2;
    else if (68 <= ele && ele <= 82)
        return 3;
    else if (83 <= ele && ele <= 98)
        return 4;
    else if (99 <= ele && ele <= 125)
        return 5;
}

// Function to print interchange stations based on the encoded station numbers
void getStn(int a[3])
{
    int c = 0;
    int i = 0;
    while (a[i])
    {
        c++;
        i++;
    }
    i = 0;
    while (a[i + 1])
    {
        int cur = a[i];
        int nxt = a[i + 1];

        if (cur == 1 && nxt == 2 || cur == 2 && nxt == 1)
            printf("\nInterchange at Majestic");
        else if (cur == 1 && nxt == 4 || cur == 4 && nxt == 1)
            printf("\nInterchange at MG Road");
        else if (cur == 1 && nxt == 5 || cur == 5 && nxt == 1)
            printf("\nInterchange at KR Pura");
        else if (cur == 3 && nxt == 5 || cur == 5 && nxt == 3)
            printf("\nInterchange at Central Silk Board");
        else if (cur == 3 && nxt == 4 || cur == 4 && nxt == 3)
            printf("\nInterchange at Jayadeva Hospital");
        else if (cur == 2 && nxt == 3 || cur == 3 && nxt == 2)
            printf("\nInterchange at Rashtreeya Vid. Road");
        else if (cur == 5 && nxt == 4 || cur == 4 && nxt == 5)
            printf("\nInterchange at Nagapura");
        i++;
    }
    printf("\n");
}

// Function to find and print the interchange stations
void InterChange()
{
    int start = encoding(tail->next->data);
    int end = encoding(tail->data);

    if (start == end)
    {
        printf("NIL");
        return;
    }

    int a[3] = {0, 0, 0};
    a[0] = start;

    struct path *head = tail->next;

    while (head != tail)
    {
        int c = encoding(head->data);
        if (c != start && c != end)
        {
            a[1] = c;
            head = tail->prev;
        }
        head = head->next;
    }

    int end_val = 0;
    if (a[1])
        a[2] = end;
    else
        a[1] = end;

    int i = 0;
	printf("(start)");
    while (a[i])
    {
		printf("->");
        switch (a[i])
        {
        case 1:
            printf("Purple");
            break;
        case 2:
            printf("Green");
            break;
        case 3:
            printf("Yellow");
            break;
        case 4:
            printf("Pink");
            break;
        case 5:
            printf("Blue");
            break;
        default:
            printf("Unknown color");
            break;
        }
        i++;
    }
	printf("->(end)");
    getStn(a);
}

//-----------------------------------------------------------------------

// Function to free the memory allocated for the circular doubly linked list
void freeStations(N *head)
{
    if (head == NULL)
    {
        return;
    }

    N *current = head;
    N *next;

    // Traverse the list and free each node
    do
    {
        next = current->next;
        free(current);
        current = next;
    } while (current != head);

    // Set the tail to NULL after freeing the memory
    tail = NULL;
}

// Function to free the memory allocated for the adjacency list
void freeGraph(struct node *adj[], int n)
{
    for (int i = 0; i < n; i++)
    {
        struct node *current = adj[i];
        struct node *next;

        // Traverse the list for each vertex and free the nodes
        while (current != NULL)
        {
            next = current->next;
            free(current);
            current = next;
        }

        adj[i] = NULL;
    }
}

//-----------------------------------------------------------------------
