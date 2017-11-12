class IOReader
{
public:
    IOReader()
    {
    }
    
    /**
     * Чтение из IO length байт
     * @param length
     * @param char*
     * @return int количество прочитанных данных
     */
    virtual int read(int length, char* buffer)
    {}

    /**
     * Запись в IO данные в buffer, length байт
     * @param buffer
     * @param length
     * @return int количество записанных данных
     */
    virtual int write(char* buffer, int length)
    {}
};