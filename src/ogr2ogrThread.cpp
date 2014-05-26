
#include "ogr2ogrThread.h"

void ogr2ogrThread::run()
{
//    parameters = parameters.replace("ogr2ogr", "");
//    parameters = parameters.replace("\\", "\\\\");
//    std::string path = QDir::toNativeSeparators(QCoreApplication::applicationFilePath()).toStdString();
//    path += parameters.toStdString();
//    std::wstring widestring = std::wstring(path.begin(), path.end());
//    LPWSTR lpwstr = const_cast<LPWSTR>(widestring.c_str());
//    STARTUPINFO si;
//    PROCESS_INFORMATION pi;
//    ZeroMemory(&si, sizeof(si));
//    si.cb = sizeof(si);
//    ZeroMemory(&pi, sizeof(pi));
//    theProgress.setValue(0);
//    if(CreateProcess(NULL, lpwstr, 0, 0, FALSE, 0, 0, 0, &si, &pi)) {
//        theProgress.setMinimum(0);
//        theProgress.setMaximum(0);
//        WaitForSingleObject(pi.hProcess, INFINITE);
//        CloseHandle(pi.hProcess);
//        CloseHandle(pi.hThread);
//        theProgress.setMaximum(100);
//        theProgress.setValue(100);
//        txtOutput.append(tr("successful.\n"));
//    } else {
//        txtOutput.append(tr("failed.\n"));
//    }
}
