#include "util/proc/proc.hpp"

#include "util/msg/msg.hpp"

#if _WIN32

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

namespace util::proc {

void run_command(const char* command) {
  static char command_buffer[32767];
  strcpy_s(command_buffer, 32767, command);

  STARTUPINFOA        si;
  PROCESS_INFORMATION pi;

  ZeroMemory(&si, sizeof(si));
  si.cb = sizeof(si);
  ZeroMemory(&pi, sizeof(pi));

  // Start the child process.
  if (!CreateProcessA(NULL,            // No module name (use command line)
                      command_buffer,  // Command line
                      NULL,            // Process handle not inheritable
                      NULL,            // Thread handle not inheritable
                      FALSE,           // Set handle inheritance to FALSE
                      0,               // No creation flags
                      NULL,            // Use parent's environment block
                      NULL,            // Use parent's starting directory
                      &si,             // Pointer to STARTUPINFO structure
                      &pi)             // Pointer to PROCESS_INFORMATION structure
  ) {
    util::msg::fatal("failed to run command [", GetLastError(), "]");
  }

  // Wait until child process exits.
  WaitForSingleObject(pi.hProcess, INFINITE);

  // Close process and thread handles.
  CloseHandle(pi.hProcess);
  CloseHandle(pi.hThread);
}

}  // namespace util::proc

#else  // ^^^ _WIN32 / !_WIN32 vvv

#include <cstdlib>

namespace util::proc {

void run_command(const char* command) { std::system(command); }

}  // namespace util::proc

#endif  // ^^^ !_WIN32
