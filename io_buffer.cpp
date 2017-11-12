class IOBuffer
{
public:
    /**
     * Чтение из IO length байт
     * @param char*
     * @param length
     * @return int количество прочитанных данных
     */
    virtual int read(char* buffer, int length) = 0;

    /**
     * Запись в IO данные в buffer, length байт
     * @param buffer
     * @param length
     * @return int количество записанных данных
     */
    virtual int write(char* buffer, int length) = 0;
};
