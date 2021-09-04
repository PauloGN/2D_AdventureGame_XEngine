#pragma once
#include<XEngine.h>

class TileMap
{

private:

	int mColumns = 0;
	int mRows = 0;

	int mutable mMapCurrentCollisionIndex = 0;
	int mutable mMapTileIndex = 0;

	std::vector<X::TextureId> mTiles;

	void loadMap(const std::filesystem::path& MapName);
	void loadTextures(const std::filesystem::path& TextureName);

public:

	std::unique_ptr<int[]> mMap = nullptr;
	//standard funcs
	void Load(const std::filesystem::path& MapName, const std::filesystem::path& TilesetName);//this function will call both load map and load textures
	void Unload();
	void Update(float deltaTime);
	void Render();
	int GetIndex(int colum, int row) const;

	// specialized funtions
	bool IsCollidingWith(const X::Math::LineSegment& lineSegment)const;
	const int& MapCurrentCollisionIndex()const { return mMapCurrentCollisionIndex; }
	const int& MapCurrentTileIndex()const { return mMapTileIndex; }
	const X::Math::Vector2& GetMapSize()const { return X::Math::Vector2(mColumns,mRows);}
	
	X::Math::Rect GetBounds()const;

	bool SetMapIndexTile(const int& index);

public:

	//Singleton Functions
	static void StaticInitialize();
	static void StaticTerminate();
	static TileMap& Get();

};

