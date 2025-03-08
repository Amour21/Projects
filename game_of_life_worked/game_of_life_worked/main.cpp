#include <windows.h>
#include <commdlg.h>  
#include <stdio.h>
#include <windowsx.h>

#define GRID_ROWS 15 
#define GRID_COLS 70
#define CELL_SIZE 20
#define TIMER_ID 1
#define TIMER_INTERVAL 100 // Èíòåðâàë òàéìåðà â ìèëëèñåêóíäàõ
int saveCounter = 0; 

void LoadConfiguration(const wchar_t* filename);
void SaveConfiguration(const wchar_t* filename);
void ToggleGame();
void UpdateGame();
void DrawGrid(HDC hdc, COLORREF liveColor, COLORREF deadColor, COLORREF borderColor);

int grid[GRID_ROWS][GRID_COLS];
bool isGameRunning = false;
HWND hwnd;
HINSTANCE hInstance;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
int ShowModeSelectionDialog(HWND hwnd);
void CreateGameMenu();
void StartNewGame();
void LoadSavedGame();


void LoadConfiguration(const wchar_t* filename) {
    FILE* file;
    errno_t err = _wfopen_s(&file, filename, L"r");
    if (err != 0) {
        MessageBox(hwnd, L"Îøèáêà ïðè îòêðûòèè ôàéëà äëÿ çàãðóçêè êîíôèãóðàöèè.", L"Îøèáêà", MB_OK | MB_ICONERROR);
        return;
    }

    int configRows, configCols;
    fscanf_s(file, "%d %d", &configRows, &configCols); 
    if (configRows > GRID_ROWS || configCols > GRID_COLS) {
        MessageBox(hwnd, L"Ðàçìåð êîíôèãóðàöèè ïðåâûøàåò ðàçìåðû èãðîâîãî ïîëÿ.", L"Îøèáêà", MB_OK | MB_ICONERROR);
        fclose(file);
        return;
    }
    
    for (int row = 0; row < GRID_ROWS; row++) {
        for (int col = 0; col < GRID_COLS; col++) {
            if (row < configRows && col < configCols) {
                fscanf_s(file, "%d", &grid[row][col]); 
            }
            else {
                grid[row][col] = 0; 
            }
        }
    }

    fclose(file);
}

void SaveConfiguration(const wchar_t* filename) {
    FILE* file;
    errno_t err = _wfopen_s(&file, filename, L"w");
    if (err != 0) {
        MessageBox(hwnd, L"Îøèáêà ïðè îòêðûòèè ôàéëà äëÿ ñîõðàíåíèÿ êîíôèãóðàöèè.", L"Îøèáêà", MB_OK | MB_ICONERROR);
        return;
    }
    fwprintf(file, L"%d %d\n", GRID_ROWS, GRID_COLS);

    for (int row = 0; row < GRID_ROWS; row++) {
        for (int col = 0; col < GRID_COLS; col++) {
            fwprintf(file, L"%d ", grid[row][col]);
        }
        fwprintf(file, L"\n");
    }

    fclose(file);
}

void SaveConfigurationWithCounter() {
    
    wchar_t filename[50];
    swprintf_s(filename, sizeof(filename) / sizeof(wchar_t), L"save_%d.txt", ++saveCounter);

    SaveConfiguration(filename);
}

void ToggleGame() {
    isGameRunning = !isGameRunning;
    if (isGameRunning) {
        SetTimer(hwnd, TIMER_ID, TIMER_INTERVAL, NULL);
    }
    else {
        KillTimer(hwnd, TIMER_ID);
    }
}

void UpdateGame() {
    int newGrid[GRID_ROWS][GRID_COLS] = { 0 };

    for (int row = 0; row < GRID_ROWS; row++) {
        for (int col = 0; col < GRID_COLS; col++) {
            int liveNeighbors = 0;
            for (int i = -1; i <= 1; i++) {
                for (int j = -1; j <= 1; j++) {
                    if (i == 0 && j == 0) continue; 
                    int r = row + i;
                    int c = col + j;
                    if (r >= 0 && r < GRID_ROWS && c >= 0 && c < GRID_COLS) {
                        liveNeighbors += grid[r][c];
                    }
                }
            }

            if (grid[row][col] == 1 && (liveNeighbors == 2 || liveNeighbors == 3)) {
                newGrid[row][col] = 1; 
            }
            else if (grid[row][col] == 0 && liveNeighbors == 3) {
                newGrid[row][col] = 1; 
            }
        }
    }
    for (int row = 0; row < GRID_ROWS; row++) {
        for (int col = 0; col < GRID_COLS; col++) {
            grid[row][col] = newGrid[row][col];
        }
    }

    InvalidateRect(hwnd, NULL, TRUE); 
}

void DrawGrid(HDC hdc, COLORREF liveColor, COLORREF deadColor, COLORREF borderColor) {
    
    HBRUSH liveBrush = CreateSolidBrush(liveColor);
    HBRUSH deadBrush = CreateSolidBrush(deadColor);
    HPEN borderPen = CreatePen(PS_SOLID, 1, borderColor);

    
    if (!liveBrush || !deadBrush || !borderPen) {
        MessageBox(hwnd, L"Îøèáêà ïðè ñîçäàíèè îáúåêòîâ ðèñîâàíèÿ.", L"Îøèáêà", MB_OK | MB_ICONERROR);
        return;
    }

    for (int row = 0; row < GRID_ROWS; row++) {
        for (int col = 0; col < GRID_COLS; col++) {
            RECT cellRect = { col * CELL_SIZE, row * CELL_SIZE, (col + 1) * CELL_SIZE, (row + 1) * CELL_SIZE };
            HBRUSH currentBrush = (grid[row][col] == 1) ? liveBrush : deadBrush;
            FillRect(hdc, &cellRect, currentBrush);

            HGDIOBJ hOldPen = SelectObject(hdc, borderPen);
            MoveToEx(hdc, cellRect.left, cellRect.top, NULL);
            LineTo(hdc, cellRect.right, cellRect.top); 
            LineTo(hdc, cellRect.right, cellRect.bottom); 
            LineTo(hdc, cellRect.left, cellRect.bottom); 
            LineTo(hdc, cellRect.left, cellRect.top);
            SelectObject(hdc, hOldPen);
        }
    }

   
    DeleteObject(liveBrush);
    DeleteObject(deadBrush);
    DeleteObject(borderPen);
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    HDC hdc;
    PAINTSTRUCT ps;
    COLORREF liveColor = RGB(128, 50, 218);
    COLORREF deadColor = RGB(204, 255, 255);
    COLORREF borderColor = RGB(255, 153, 153);

    switch (uMsg) {
    case WM_PAINT:
        hdc = BeginPaint(hwnd, &ps);
        DrawGrid(hdc, liveColor, deadColor, borderColor);
        EndPaint(hwnd, &ps);
        break;

    case WM_LBUTTONDOWN: {
        int mouseX = GET_X_LPARAM(lParam);
        int mouseY = GET_Y_LPARAM(lParam);
        int row = mouseY / CELL_SIZE;
        int col = mouseX / CELL_SIZE;

        if (row < GRID_ROWS && col < GRID_COLS) {
            grid[row][col] = 1 - grid[row][col];
            InvalidateRect(hwnd, NULL, TRUE);
        }
        break;
    }
    case WM_KEYDOWN: {
        if (wParam == VK_SPACE) {
            ToggleGame();
        }
        if (wParam == VK_F5) { 
            SaveConfigurationWithCounter();
        }
        break;
    }

    case WM_TIMER:
        if (isGameRunning) {
            UpdateGame();
        }
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    return 0;
}


int ShowModeSelectionDialog(HWND hwnd) {
    int result = MessageBox(hwnd, L"Âûáåðèòå ðåæèì èãðû\n Äà - Íîâàÿ èãðà\n Íåò - Çàãðóçèòü èãðó\n Ñïðàâêà: ïðîáåë - ïàóçà \n f5 ñîõðàíåíèå",
        L"Ìåíþ", MB_YESNO | MB_ICONQUESTION);
    return result;
}

void StartNewGame() {

    for (int row = 0; row < GRID_ROWS; row++) {
        for (int col = 0; col < GRID_COLS; col++) {
            grid[row][col] = 0;
        }
    }


    InvalidateRect(hwnd, NULL, TRUE);
}


void LoadSavedGame() {
    OPENFILENAME ofn;       
    wchar_t szFile[260];    


    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = hwnd;
    ofn.lpstrFile = szFile;
    ofn.lpstrFile[0] = '\0';
    ofn.nMaxFile = sizeof(szFile);
    ofn.lpstrFilter = L"Text files\0*.TXT\0All files\0*.*\0";
    ofn.nFilterIndex = 1;
    ofn.lpstrFileTitle = NULL;
    ofn.nMaxFileTitle = 0;
    ofn.lpstrInitialDir = NULL;
    ofn.lpstrTitle = L"Âûáåðèòå ôàéë ñîõðàíåíèÿ";
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;


    if (GetOpenFileName(&ofn) == TRUE) {
        LoadConfiguration(ofn.lpstrFile);
        InvalidateRect(hwnd, NULL, TRUE);
    }
}


void CreateGameMenu() {
    int mode = ShowModeSelectionDialog(hwnd);

    if (mode == IDYES) {
        StartNewGame(); 
    }
    else if (mode == IDNO) {
        LoadSavedGame();
    }
    else {
        PostQuitMessage(0);
    }
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
  
    WNDCLASS wc = { 0 };
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = L"LifeGameClass";
    RegisterClass(&wc);

   
    hwnd = CreateWindowEx(0, L"LifeGameClass", L"Èãðà Æèçíü",
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
        800, 600, NULL, NULL, wc.hInstance, NULL);

    if (hwnd == NULL) {
        return 0;
    }

    CreateGameMenu();  

 
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}
