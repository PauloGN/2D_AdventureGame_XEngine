#include "TileMap.h"
#include "XCamera.h"

namespace
{
	// this should change based on the texture size that I am using
	const float tileSize = 32.0f;
	// pointer to the object of the class
	std::unique_ptr<TileMap> tileMapInstance;
	int tileIndex = 0;

}



int TileMap::GetIndex(int colum, int row) const
{
	//Example: 
	//if looking for colum 1 and row 3 with 10 total colums 
	// index = 1 + (3 * 10)	
	// index = 31;
	return colum + (row * mColumns);
}

void TileMap::loadMap(const std::filesystem::path& fileName)
{
	//prevente to call the load map twice
	if (mMap)
	{
		mMap.reset();
	}

	FILE* file = nullptr;//create the file
	fopen_s(&file, fileName.u8string().c_str(), "r"); // open the file through the file name, converte to u8string and character chain, "r" read

	fscanf_s(file, "Columns: %d\n", &mColumns); // inside the file get the value based on the token and assign into the variable
	fscanf_s(file, "Rows: %d\n", &mRows); // inside the file get the value based on the token and assign into the variable

	// now we have the size of columns and rows we can create the array map that will be rendered on screen
	mMap = std::make_unique<int[]>(mColumns * mRows);

	for (int y = 0; y < mRows; y++)
	{
		for (int x = 0; x < mColumns; x++)
		{									  // first iteration          0 + (0 * 30)
			const int index = GetIndex(x, y); // function GetTndex returns x + (y * mColumns);
											//  second iteration         1 + (0 * 30);

			mMap[index] = fgetc(file) - '0';
			/*
				representation of number in charracter regardin Ascci table is

				(0 = 48, 1 = 49, 2 = 50,..... 9 = 57)

				then to convert a char to the correspondent int number, we subtrat the char '0' which is 48 from any char (from '0' to '9')
				and it will return the corespondent int.

			*/

		}

		fgetc(file);//read and jump to the next line
	}

	fclose(file);
}

void TileMap::loadTextures(const std::filesystem::path& fileName)
{

	mTiles.clear();//prevents to get an old vector full of informations

	FILE* file = nullptr;
	fopen_s(&file, fileName.u8string().c_str(), "r");

	int count = 0;// range of the loop

	fscanf_s(file, "Count: %d\n", &count);

	for (int i = 0; i < count; i++)
	{
		char buffer[256];
		fscanf_s(file, "%s\n", buffer, static_cast<int>(std::size(buffer)));
		mTiles.push_back(X::LoadTexture(buffer));

	}

	fclose(file);

}

void TileMap::Load(const std::filesystem::path& MapName, const std::filesystem::path& TilesetName)
{
	//to keep things nice and clean this fuction call both =>
	loadMap(MapName);
	loadTextures(TilesetName);
}

void TileMap::Unload()
{
	// reset variables, pointers, vectors and so on...
	mTiles.clear();
	mColumns = 0;
	mRows = 0;
	mMap.reset();
}

void TileMap::Update(float deltaTime)
{

	//Empty

}

void TileMap::Render()
{

	for (int y = 0; y < mRows; y++)
	{

		for (int x = 0; x < mColumns; x++)
		{
			const int mapIndex = GetIndex(x, y);
			const int tileIndex = mMap[mapIndex];//mMap is an array that maps all the screen positions to render the apropriate image.
			const X::TextureId textureid = mTiles.at(tileIndex);// tileIndex got the number of the object that will be rendered on screen

			
			const X::Math::Vector2 worldPosition = { x * tileSize, y * tileSize };
			const X::Math::Vector2 screenPosition = XCamera::Get().ConverteToScreenPosition(worldPosition);


			X::DrawSprite(textureid, screenPosition, X::Pivot::TopLeft);
		}

	}

}

bool TileMap::IsCollidingWith(const X::Math::LineSegment& lineSegment) const
{

	const int startX = static_cast<int> (lineSegment.from.x / tileSize); // StarX is a 2d point it is the start of the lineSegment represented in 2 Dimentions axis x and y(a vector2)
	const int startY = static_cast<int> (lineSegment.from.y / tileSize);// the initial point of the lineSegment of Y
	const int endX = static_cast<int> (lineSegment.to.x / tileSize);// the end of the lineSegment of X.
	const int endY = static_cast<int> (lineSegment.to.y / tileSize);// the end of the lineSegment of y.

	// start

	if (startX < 0 || startX >= mColumns ||
		startY < 0 || startY >= mRows ||
		endX < 0 || endX >= mColumns ||
		endY < 0 || endY >= mRows)
	{
		return true;
	}

	for (int y = startY; y <= endY; y++)
	{
		for (int x = startX; x <= endX; ++x)
		{
			const int index = GetIndex(x, y);

			if (mMap[index] > 1 && mMap[index] < 23 ||( mMap[index] > 35))
			{
				tileIndex = index; // takes map collision index position into the array
				mMapCurrentCollisionIndex = index; //Sprite visual representation
				mMapTileIndex = mMap[index];
				return true;
			}

		}

	}

	mMapCurrentCollisionIndex = 0;
	mMapTileIndex = 0;

	return false;
}

X::Math::Rect TileMap::GetBounds() const
{
	return
	{
		0.0f,				// left
		0.0f,				// top
		mColumns * tileSize,// right
		mRows * tileSize	// bottom
	};
	//return X::Math::Rect();
}

bool TileMap::SetMapIndexTile(const int& index)
{

	if (mMap[index] == 18 || mMap[index] == 21)
	{
		mMap[index] = 35;//green
		return true;
	}
	else if(mMap[index] == 19 || mMap[index] == 20)
	{
		mMap[index] = 34; // brown
		return true;
	}
	else if (mMap[index] == 36 || mMap[index] == 37 || mMap[index] == 38 || mMap[index] == 39)
	{
		mMap[index] = 0; //green grass
		return true;
	}

	return false;
}


//-------------------------------------------------------------------------------------------------------------------------------------
//Singleton Static functions


void TileMap::StaticInitialize()
{
	//prevente more than one initialization
	XASSERT(tileMapInstance == nullptr, "WRONG!!!Inicialize the object already exists");
	tileMapInstance = std::make_unique<TileMap>();//instantiate the object
}

void TileMap::StaticTerminate()
{
	//reset the unique pointer that points to the object of the class
	tileMapInstance.reset();
}

TileMap& TileMap::Get()
{
	//prevente to get an empty object
	XASSERT(tileMapInstance != nullptr, "WRONG!!! objec not initualized yet...");
	//return a ponter to the object internally instatiated
	return *tileMapInstance;

	// TODO: insert return statement here
}
