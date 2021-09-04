#include "ChasingCalculation.h"

X::Math::Vector2 ChasingCalculation::findPath(X::Math::Vector2 origin, X::Math::Vector2 destination)
{

   const X::Math::Vector2 mapSize = TileMap::Get().GetMapSize();

   const int x = (int)mapSize.x;
   const int y = (int)mapSize.y;

   int currentX = (int)origin.x;
   int currentY = (int)origin.y;

   int destinationX = (int)destination.x;
   int destinationY = (int)destination.y;

   bool** visited = new bool* [x];
   int** cost = new int* [x];
   X::Math::Vector2** previous = new X::Math::Vector2 * [x];

    for (size_t i = 0; i < x; i++)
    {

        visited[i] = new bool[y];
        cost[i] = new int[y];
        previous[i] = new X::Math::Vector2[y];

    }


    for (size_t i = 0; i < x; i++)
    {

        for (size_t j = 0; j < y; j++)
        {

            visited[i][j] = false;
            cost[i][j] = INT_MAX;
            previous[i][j] = X::Math::Vector2(-1, -1);

        }

    }

    visited[currentX][currentY] = true;
    cost[currentX][currentY] = 0;

    int tile;
    int tileNumber;

    while (!visited[destinationX][destinationY])
    {

        if (currentX >= 0)
        {
            if (currentY >= 0)
            {
                tile = TileMap::Get().GetIndex(currentX - 1, currentY - 1);
                tileNumber = TileMap::Get().mMap[tile];
                if (tileNumber < 2 || (tileNumber > 22 && tileNumber < 36))
                {

                }

            }
        }

    }
   


    // delete
    for (size_t i = 0; i < x; i++)
    {

       delete [] visited[i];
       delete[] cost[i];
       delete[] previous[i];

    }

    delete[] visited;
    delete[] cost;
    delete[] previous;

    return X::Math::Vector2();
}
