#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

const int Cut = 12; //Stopping limit ("Cut") for the ID search, since solution will never go a depth above 11.

class game
{
public:
    int m, c, b;    // m = missionaries,  c = cannibals, b = boat side (0 or 1) 
};

enum tree { Fail, Incomplete, Goal };

// Printing current situation
void printmc(game game1)
{
    cout << "\n\n\n";
    cout << "Left Side \t\t\t Right Side" << endl;
    for (int i = 0; i < game1.m; i++)
    {
        cout << " M " << " ";
    }
    for (int i = 0; i < game1.c; i++)
    {
        cout << " C " << " ";
    }
    cout << "\t \t";
    for (int i = 0; i < 3 - game1.m; i++)
    {
        cout << " M " << " ";
    }
    for (int i = 0; i < 3 - game1.c; i++)
    {
        cout << " C " << " ";
    }
    cout << endl << endl; 
    if (game1.b == 1)
    {
        cout << "The boat is on the left side" << endl;
    }
    if (game1.b == 0)
    {
        cout << "The boat is on the right side" << endl;
    }
}

// Checking if action is valid
bool validAction(int action, game game1) 
{
    int m, c;
    
    if (action < 5) 
    {
        if (game1.b == 0) 
        {
            return false;
        }
        m = game1.m;
        c = game1.c;
    }
    
    else 
    {
        if (game1.b == 1) 
        {
            return false;
        }
        m = 3 - game1.m;
        c = 3 - game1.c;
    }

    action = action % 5;
    
    return(action == 0 && m >= 1) || (action == 1 && m >= 2) || (action == 2 && c >= 1) || (action == 3 && c >= 2) || (action == 4 && m >= 1 && c >= 1);
}

//Moving cannibals or missionaries
game move(int action, game game1) 
{
    int direction;
    if (action < 5) 
    {
        direction = - 1;
    }
    else 
    {
        direction = 1;
    }
 
    action = action % 5;
    
    game1.b = (game1.b + 1) % 2;
    
    switch (action) 
    {
    case 0:
        game1.m += direction * 1;
        break;
    case 1:
        game1.m += direction * 2;
        break;
    case 2:
        game1.c += direction * 1;
        break;
    case 3:
        game1.c += direction * 2;
        break;
    case 4:
        game1.m += direction * 1;
        game1.c += direction * 1;
        break;
    default:
        break;
    }
    return game1;
}

// Interactive Deepening Search (With cut 11)
tree solution(game game1, int limit, vector<game>* optimalSol)
{
    if (!((game1.m == 0 || game1.m >= game1.c) && (3 - game1.m == 0 || 3 - game1.m >= 3 - game1.c))) 
    {
        return Fail;
    }

    if (game1.m == 0 && game1.c == 0 && game1.b == 0) 
    {
        optimalSol->push_back(game1);
        return Goal;
    }
    
    if (limit == 0) {
        return Incomplete;
    }
    
    tree node = Fail;
    
    for (int a = 0; a < Cut; a++) 
    {
        if (validAction(a, game1)) 
        {
            tree st = solution(move(a, game1), limit - 1, optimalSol);
            if (st == Goal) 
            {
                optimalSol->push_back(game1);
                return Goal;
            }
            else if (st == Incomplete) 
            {
                node = Incomplete;
            }
        }
    }
    return node;
}

void printNode(tree node, int limit) 
{
    cout << "Limit: " << limit << endl;
    switch (node)
    {
    case Fail:
        cout << "No Solution found" << endl;
        break;
    case Incomplete:
        cout << "Looking for solution" << endl;
        break;
    case Goal:
        cout << "Solution Found!" << endl;
        break;
    default:
        break;
    }
}

void main()
{
    game game1;
    game1.m = 3;
    game1.c = 3;
    game1.b = 1;
    printmc(game1);


    vector<game> optimalSol;
    tree node = Incomplete;
    int limit = 1;

    while (node == Incomplete) 
    {

        node = solution(game1, limit, &optimalSol);
        printNode(node, limit);
        limit++;
    }

    cout << endl << "The optimal solution is:" << endl;

    for (int i = 0; i < optimalSol.size();i++) 
    {
        game1.m = optimalSol[i].m;
        game1.c = optimalSol[i].c;
        game1.b = optimalSol[i].b;
        printmc(game1);
    }

}