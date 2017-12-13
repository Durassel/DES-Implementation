char *generateBitBlockFromInt(int outputvalue)
{
    char *result = new char[4];

    for (int i = 0; i < 4; i++)
    {
        result[i] = (outputvalue / 8) % 2;
        outputvalue *= 2;
    }

    return result;
}

int generateIntFromBitBlock(char *block, long blocksize)
{
    int result = 0;

    for (int i = 0; i < blocksize; i++)
    {
        result = (2 * result + block[i]);
    }

    return result;
}
