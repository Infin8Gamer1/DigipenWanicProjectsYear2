SET RETURNVALUE= 0

SET ms_flags=/W3 /WX /sdl /Od /Oy- /EHsc
SET driver=%1
SET output=%2
SET files=%driver%.cpp myArray.cpp
SET obj_files=%driver%.obj myArray.obj

SET exe_name=ms%current_test_number%.exe

SET ms_files_to_delete= %exe_name% *.pdb %obj_files% "StudentOutput%current_test_number%.txt" "drout%current_test_number%.txt" "memLeak%current_test_number%.txt" "ms_report%current_test_number%.txt" "fc_report%current_test_number%.txt"

CL.exe /nologo %ms_flags% %files% /Fe%exe_name% > "ms_report%current_test_number%.txt" 2>&1
IF NOT EXIST %exe_name% GOTO BUILDING_FAIL

%exe_name% > StudentOutput%current_test_number%.txt

FC.exe %output% "StudentOutput%current_test_number%.txt" > "fc_report%current_test_number%.txt"
if %errorlevel% neq 0 GOTO DIFF_FAIL


GOTO MEMORY

:BUILDING_FAIL
SET RETURNVALUE= 1
echo ************************************************
echo ******************BUILD ERROR*******************  
echo ************************************************    
more ms_report%current_test_number%.txt

GOTO DONE

:DIFF_FAIL
SET RETURNVALUE= 2
echo ************************************************
echo ******************DIFF ERROR********************  
echo ************************************************    
more fc_report%current_test_number%.txt

:MEMORY
drmemory.exe 2> "memLeak%current_test_number%.txt" -results_to_stderr -batch -exit_code_if_errors 1 -- %exe_name% > "drout%current_test_number%.txt"
if %errorlevel% neq 0 GOTO MEMORY_LEAK

GOTO DONE

:MEMORY_LEAK
IF %RETURNVALUE% equ 2 (SET RETURNVALUE= 4) ELSE (SET RETURNVALUE= 3)
echo ************************************************
echo **************MEMORY LEAK ERROR*****************  
echo ************************************************ 
more memLeak%current_test_number%.txt

:DONE
del %ms_files_to_delete%