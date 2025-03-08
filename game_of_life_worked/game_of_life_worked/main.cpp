#include <windows.h>
#include <commdlg.h>  // Для диалогового окна выбора файла
#include <stdio.h>
#include <windowsx.h>

#define GRID_ROWS 15 
#define GRID_COLS 70
#define CELL_SIZE 20
#define TIMER_ID 1
#define TIMER_INTERVAL 100 // Интервал таймера в миллисекундах
int saveCounter = 0; // спец переменная для сохранений
// Объявления функций
void LoadConfiguration(const wchar_t* filename);
void SaveConfiguration(const wchar_t* filename);
void ToggleGame();
void UpdateGame();
void DrawGrid(HDC hdc, COLORREF liveColor, COLORREF deadColor, COLORREF borderColor);

// Глобальные переменные
int grid[GRID_ROWS][GRID_COLS];
bool isGameRunning = false;
HWND hwnd;
HINSTANCE hInstance;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
int ShowModeSelectionDialog(HWND hwnd);
void CreateGameMenu();
void StartNewGame();
void LoadSavedGame();

// Функции для загрузки и сохранения конфигурации
void LoadConfiguration(const wchar_t* filename) {
    FILE* file;
    errno_t err = _wfopen_s(&file, filename, L"r");
    if (err != 0) {
        MessageBox(hwnd, L"Ошибка при открытии файла для загрузки конфигурации.", L"Ошибка", MB_OK | MB_ICONERROR);
        return;
    }

    int configRows, configCols;
    fscanf_s(file, "%d %d", &configRows, &configCols); // Считываем размеры конфигурации из файла
    if (configRows > GRID_ROWS || configCols > GRID_COLS) {
        MessageBox(hwnd, L"Размер конфигурации превышает размеры игрового поля.", L"Ошибка", MB_OK | MB_ICONERROR);
        fclose(file);
        return;
    }
    // Проверяем, что размеры конфигурации не превышают размеров игрового поля
    for (int row = 0; row < GRID_ROWS; row++) {
        for (int col = 0; col < GRID_COLS; col++) {
            if (row < configRows && col < configCols) {
                fscanf_s(file, "%d", &grid[row][col]); // Считываем клетку из файла
            }
            else {
                grid[row][col] = 0; // Заполняем оставшиеся клетки нулями
            }
        }
    }

    fclose(file);
}

void SaveConfiguration(const wchar_t* filename) {
    FILE* file;
    errno_t err = _wfopen_s(&file, filename, L"w");
    if (err != 0) {
        MessageBox(hwnd, L"Ошибка при открытии файла для сохранения конфигурации.", L"Ошибка", MB_OK | MB_ICONERROR);
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
    // Формируем имя файла на основе счётчика
    wchar_t filename[50];
    swprintf_s(filename, sizeof(filename) / sizeof(wchar_t), L"save_%d.txt", ++saveCounter);

    // Сохраняем конфигурацию
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

            // Проверяем соседей
            for (int i = -1; i <= 1; i++) {
                for (int j = -1; j <= 1; j++) {
                    if (i == 0 && j == 0) continue; // Пропускаем саму клетку
                    int r = row + i;
                    int c = col + j;
                    if (r >= 0 && r < GRID_ROWS && c >= 0 && c < GRID_COLS) {
                        liveNeighbors += grid[r][c];
                    }
                }
            }

            // Применяем правила "Жизни"
            if (grid[row][col] == 1 && (liveNeighbors == 2 || liveNeighbors == 3)) {
                newGrid[row][col] = 1; // Клетка остается живой
            }
            else if (grid[row][col] == 0 && liveNeighbors == 3) {
                newGrid[row][col] = 1; // Клетка рождается
            }
        }
    }

    // Копируем новое состояние обратно в сетку
    for (int row = 0; row < GRID_ROWS; row++) {
        for (int col = 0; col < GRID_COLS; col++) {
            grid[row][col] = newGrid[row][col];
        }
    }

    InvalidateRect(hwnd, NULL, TRUE); // Перерисовываем окно
}

void DrawGrid(HDC hdc, COLORREF liveColor, COLORREF deadColor, COLORREF borderColor) {
    
    HBRUSH liveBrush = CreateSolidBrush(liveColor);
    HBRUSH deadBrush = CreateSolidBrush(deadColor);
    HPEN borderPen = CreatePen(PS_SOLID, 1, borderColor);

    
    if (!liveBrush || !deadBrush || !borderPen) {
        MessageBox(hwnd, L"Ошибка при создании объектов рисования.", L"Ошибка", MB_OK | MB_ICONERROR);
        return;
    }

    for (int row = 0; row < GRID_ROWS; row++) {
        for (int col = 0; col < GRID_COLS; col++) {
            RECT cellRect = { col * CELL_SIZE, row * CELL_SIZE, (col + 1) * CELL_SIZE, (row + 1) * CELL_SIZE };

            // Выбираем кисть в зависимости от состояния клетки
            HBRUSH currentBrush = (grid[row][col] == 1) ? liveBrush : deadBrush;
            FillRect(hdc, &cellRect, currentBrush);

            // Рисуем рамку вокруг клетки
            HGDIOBJ hOldPen = SelectObject(hdc, borderPen);
            MoveToEx(hdc, cellRect.left, cellRect.top, NULL);
            LineTo(hdc, cellRect.right, cellRect.top); // Верхняя граница
            LineTo(hdc, cellRect.right, cellRect.bottom); // Правая граница
            LineTo(hdc, cellRect.left, cellRect.bottom); // Нижняя граница
            LineTo(hdc, cellRect.left, cellRect.top); // Левая граница
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
        if (wParam == VK_F5) { // Сохранение при нажатии F5
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

// Диалог выбора режима игры
int ShowModeSelectionDialog(HWND hwnd) {
    int result = MessageBox(hwnd, L"Выберите режим игры\n Да - Новая игра\n Нет - Загрузить игру\n Справка: пробел - пауза \n f5 сохранение",
        L"Меню", MB_YESNO | MB_ICONQUESTION);
    return result;
}

// Начало новой игры
void StartNewGame() {
    // Инициализируем сетку для новой игры
    for (int row = 0; row < GRID_ROWS; row++) {
        for (int col = 0; col < GRID_COLS; col++) {
            grid[row][col] = 0;
        }
    }

    // Перерисовываем окно
    InvalidateRect(hwnd, NULL, TRUE);
}

// Функция для выбора файла с конфигурацией игры
void LoadSavedGame() {
    OPENFILENAME ofn;       // Структура для выбора файла
    wchar_t szFile[260];    // Буфер для хранения пути к файлу

    // Инициализируем структуру OPENFILENAME
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
    ofn.lpstrTitle = L"Выберите файл сохранения";
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

    // Открытие диалогового окна выбора файла
    if (GetOpenFileName(&ofn) == TRUE) {
        LoadConfiguration(ofn.lpstrFile);
        InvalidateRect(hwnd, NULL, TRUE); // Перерисовываем окно
    }
}

// Главное окно
void CreateGameMenu() {
    int mode = ShowModeSelectionDialog(hwnd);

    if (mode == IDYES) {
        StartNewGame(); // Начинаем новую игру
    }
    else if (mode == IDNO) {
        LoadSavedGame(); // Загружаем игру из файла
    }
    else {
        PostQuitMessage(0);
    }
}

// Точка входа для Windows-приложений
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // Регистрация класса окна
    WNDCLASS wc = { 0 };
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = L"LifeGameClass";
    RegisterClass(&wc);

    // Создание окна
    hwnd = CreateWindowEx(0, L"LifeGameClass", L"Игра Жизнь",
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
        800, 600, NULL, NULL, wc.hInstance, NULL);

    if (hwnd == NULL) {
        return 0;
    }

    CreateGameMenu();  // Показываем диалог выбора режима игры

    // Показать окно и запустить цикл обработки сообщений
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}