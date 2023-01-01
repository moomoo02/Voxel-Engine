#ifndef __BLOCK_H__
#define __BLOCK_H__

enum BlockType {
    BlockType_Default = 0,
    BlockType_Grass,
    BlockType_Dirt,
    BlockType_Water,
    BlockType_Stone,
    BlockType_Wood,
    BlockType_Sand,
    BlockType_NumTypes,
};


class Block {
public:
    Block();
    ~Block();
    bool isActive();
    void setActive();
private:
    bool active;
    BlockType blockType;
};
#endif // __BLOCK_H__