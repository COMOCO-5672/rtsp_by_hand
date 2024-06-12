#include <stdio.h>
#include <iostream>
#include <memory>

class H264File
{
private:
    FILE *m_file_ { nullptr};
    char *m_buf_ { nullptr };
    int m_buf_size_ { 0 };
    int m_buf_used_ { 0 };
    int m_count_ { 0 };

public:
    H264File(int buf_size = 500000);
    ~H264File();

    bool Open(const char *path);
    void Close();

    bool IsOpened() const
    {
        return m_file_!= nullptr;
    }

    int ReadFrame(char* in_buf, int in_buf_size, bool end);
};

int main()
{
    H264File h264_file;
    if (!h264_file.Open("test.h264")) {
        printf("open file failed\n");
        return -1;
    }

    std::string suffix = "live";
    std::string ip = "127.0.0.1";
    std::string port = "554";
    std::string rtsp_url = "rtsp://" + ip + ":" + port + "/" + suffix;

    std::shared_ptr<>

}