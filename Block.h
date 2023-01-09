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
    Block(bool active, BlockType blockType);
    ~Block();
    bool isActive(bool status);
    void setActive();
    BlockType getBlockType();
private:
    bool active;
    BlockType blockType;
};
#endif // __BLOCK_H__