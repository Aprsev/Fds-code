#include<stdio.h>
#include<stdlib.h>

static int graph[1005][1005];/*matrix to instore information of edges,
0 stands for no link and positive integer stands for weight of edges*/
int dist[1005];//length of shortest path
int known[1005];//mark the state of vertex
int path[1005];//record former vertex in the shortest pash

int check_min(int chosen,int nv)//check if 'chosen' has minimum distance
{
    for(int i=1;i<=nv;i++)
    {
        if((known[i]==0)&&(dist[i]<dist[chosen]))
            return 1;
    }
    return 0;
}

int Dijkstra(int nv, FILE *file)//function to check validity of a sequence
{
    int s,v;
    int flag=0;
    for(int i=1;i<=nv;i++){//initialization
        known[i]=0;//mark all vertex as unknown
        dist[i]=100000000;//set the distance to infinity
        path[i]=0;//set the former vertex to 0
    }
    fscanf(file, "%d", &s);
    dist[s]=0;//set the distance of the source vertex to 0
    for(int i=1;i<=nv;i++)
    {
        int chosen;//variable to store unkown vertex of minimum distance
        if(i==1)
            chosen=s;
        else{//use the next vertex in the sequence as 'chosen'
            fscanf(file, "%d", &chosen);
        }

        if(check_min(chosen,nv)){//if the vertex in the sequence does not have minimun distance then flag=1
            flag=1;
        }
        if(flag){
            continue;
        }

        known[chosen]=1;//mark 'chosen' as known
        for(int j=1;j<=nv;j++)//check all vertex adjcent to 'chosen'
        {
            if(graph[chosen][j]>0)//if there exists an edge
            {
                if((known[j]==0)&&(dist[chosen]+graph[chosen][j]<dist[j]))//if the shortest path can be updated
                {
                    dist[j]=dist[chosen]+graph[chosen][j];//update the shortest path
                    path[j]=chosen;//record the former vertex
                }
            }
        }
    }
    if(flag)
        return 0;
    else
        return 1;
}

int main()
{
    FILE *file;
    FILE *fp;
    fp = fopen("results.txt", "w+");//open file to write
    
    int choice;
    printf("Please enter the file number:\n");
    scanf("%d",&choice);
    switch(choice)//choose the file to read
    {
        case 1:file=fopen("case1.txt","r");break;
        case 2:file=fopen("case2.txt","r");break;
        default:printf("Invalid file number\n");return 0;
    }

    int nv,ne,k;//initialize the number of vertex, number of edges and number of sequences
    fscanf(file, "%d", &nv);
    fscanf(file, "%d", &ne);

    int v1,v2,weight;
    for(int i=0;i<ne;i++)//initialize the adjacent matrix
    {
        fscanf(file, "%d", &v1);
        fscanf(file, "%d", &v2);
        fscanf(file, "%d", &weight);
        graph[v1][v2]=graph[v2][v1]=weight;//set the weight of edges
    }

    fscanf(file, "%d", &k);
    for(int i=0;i<k;i++)
    {
        if(Dijkstra(nv, file))//if is a valid dijkstra sequence 
            fprintf(fp,"Yes\n");
        else//if not a valid dijkstra sequence
            fprintf(fp,"No\n");
    }

    fclose(file);
    return 0;
}