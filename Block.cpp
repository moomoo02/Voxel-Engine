#include "Block.h"

Block::Block()
{
    active = false;
    blockType = BlockType::BlockType_Default;
}

Block::Block(bool act, BlockType type)
{
    active = act;
    blockType = type;
}

Block::~Block()
{

}

bool Block::isActive()
{
    return active;
}

void Block::setActive()
{
    active = 1;
}

BlockType Block::getBlockType(){
    return blockType;
}