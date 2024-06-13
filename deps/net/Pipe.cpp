#pragma once

namespace Pipe {
class Pipe {
  public:
    Pipe();
    virtual ~Pipe();
    bool Create();
    int Write();
    int Read();
    void Close();

    
}
} // namespace Pipe