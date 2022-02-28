#include <stdio.h>
#include <time.h>
#include <windows.h>
#include <chrono>

class Block{
    public:
    char screen[20][10];
    int block_num;
    int stop_block{0};
    char pos[2];
    char px_pos[4][2];
    void set_screen(char[20][10]);
    void down();
    void right();
    void left();
    void left_rotate();
    void right_rotate();
    int create_block(int[7]);
    void lock_block();
    void update();
    void render();
    void clear();
};

int Block::create_block(int blocks[7]){
    srand(time(0));
    int count{0};
    int block{blocks[rand()%7]};
    for(int i{0}; i < 8; ++i){
        int px{(block >> i) & 1};
        if (px == 1){
            if (screen[int(i/4)][(i%4)+3] == 79){
                return 1;
                break;
            }
            screen[int(i/4)][(i%4)+3] = 219;
            px_pos[count][0] = (i%4)+3;
            px_pos[count][1] = int(i/4);
            count += 1;
        }
    }
    pos[0] = 5;
    pos[1] = 0;
    block_num = block;
    return 0;
}
void Block::down(){
    bool place{true};
    for(int i{0}; i < 4; ++i){
        if (screen[px_pos[i][1]+1][px_pos[i][0]] == 79 || px_pos[i][1]+1 > 19){
            place = false;
            stop_block += 1;
            break;
        }
    }
    if (place){
        for(int i{0}; i < 4; ++i){
            screen[px_pos[i][1]][px_pos[i][0]] = 249;
        }
        for(int i{0}; i < 4; ++i){
            px_pos[i][1] += 1;
            screen[px_pos[i][1]][px_pos[i][0]] = 219;
        }
        pos[1] += 1;
    }
}

void Block::right(){
    bool place{true};
    for(int i{0}; i < 4; ++i){
        if (screen[px_pos[i][1]][px_pos[i][0]+1] == 79 || px_pos[i][0]+1 > 9){
            place = false;
            break;
        }
    }
    if (place){
        for(int i{0}; i < 4; ++i){
            screen[px_pos[i][1]][px_pos[i][0]] = 249;
        }
        for(int i{0}; i < 4; ++i){
            px_pos[i][0] += 1;
            screen[px_pos[i][1]][px_pos[i][0]] = 219;
        }
        pos[0] += 1;
    }
}

void Block::left(){
    bool place{true};
    for(int i{0}; i < 4; ++i){
        if (screen[px_pos[i][1]][px_pos[i][0]-1] == 79 || px_pos[i][0]-1 < 0){
            place = false;
            break;
        }
    }
    if (place){
        for(int i{0}; i < 4; ++i){
            screen[px_pos[i][1]][px_pos[i][0]] = 249;
        }
        for(int i{0}; i < 4; ++i){
            px_pos[i][0] -= 1;
            screen[px_pos[i][1]][px_pos[i][0]] = 219;
        }
        pos[0] -= 1;
    }
}

void Block::left_rotate(){
    bool place{true};
    if (block_num != 102){
        int local_pos[4][2];
        for(int i{0}; i < 4; ++i){
            local_pos[i][0] = pos[0] - px_pos[i][0];
            local_pos[i][1] = pos[1] - px_pos[i][1];
        }
        for(int i{0}; i < 4; ++i){
            if (screen[pos[1] - local_pos[i][0]][pos[0] + local_pos[i][1]] == 79 || pos[1] - local_pos[i][0] > 19 || pos[0] + local_pos[i][1] > 9 || pos[0] + local_pos[i][1] < 0){
                place = false;
                break;
            }
        }
        if (place){
            for(int i{0}; i < 4; ++i){
                screen[px_pos[i][1]][px_pos[i][0]] = 249;
                px_pos[i][1] = pos[1] - local_pos[i][0];
                px_pos[i][0] = pos[0] + local_pos[i][1];
            }
            for(int i{0}; i < 4; ++i){
                screen[px_pos[i][1]][px_pos[i][0]] = 219;
            }
        }
    }
}

void Block::right_rotate(){
    bool place{true};
    int local_pos[4][2];
    if (block_num != 102){
        for(int i{0}; i < 4; ++i){
            local_pos[i][0] = pos[0] - px_pos[i][0];
            local_pos[i][1] = pos[1] - px_pos[i][1];
        }
        for(int i{0}; i < 4; ++i){
            if (screen[pos[1] + local_pos[i][0]][pos[0] - local_pos[i][1]] == 79 || pos[1] + local_pos[i][0] > 19 || pos[0] - local_pos[i][1] > 9 || pos[0] - local_pos[i][1] < 0){
                place = false;
                break;
            }
        }
        if (place){
            for(int i{0}; i < 4; ++i){
                screen[px_pos[i][1]][px_pos[i][0]] = 249;
                px_pos[i][1] = pos[1] + local_pos[i][0];
                px_pos[i][0] = pos[0] - local_pos[i][1];
            }
            for(int i{0}; i < 4; ++i){
                screen[px_pos[i][1]][px_pos[i][0]] = 219;
            }
        }
    }
}
void Block::lock_block(){
    for(int i{0}; i<4; ++i){
        screen[px_pos[i][1]][px_pos[i][0]] = 79;
    }
}

void Block::render(){
    for(int y{0}; y<20; y++){
        printf("%.*s\n",10, screen[y]);
    }
}

void Block::clear(){
    int count{0}; 
    for(int i{0}; i<20; ++i){
        for(int j{0}; j<10; ++j){
            if (screen[i][j] == 79){
                count += 1;
            }
        }    
        if(count == 10){
            for (int y{0}; y<19; ++y){
                if (19-y <= i){
                    for (int x{0}; x<10; ++x){
                        screen[19-y][x] = screen[19-y-1][x];        
                    }
                }
            }
        }
        count = 0;
    }
}

void Block::update(){
    int BLOCKS[7] {78, 142, 198, 102, 108, 46, 15};
    auto start{std::chrono::high_resolution_clock::now()};
    auto end{std::chrono::high_resolution_clock::now()};
    while (1){
        if (create_block(BLOCKS)){
            break;
        }
        while(1){
            std::system("cls");
            render();
            end = std::chrono::high_resolution_clock::now();
            if (std::chrono::duration_cast<std::chrono::microseconds>( end - start ).count() > 200000){
                down();
                start = std::chrono::high_resolution_clock::now();
            }
            if (GetAsyncKeyState(0x28)){ //down arrow
                down();
            }
            if (stop_block > 3){
                stop_block = 0;
                lock_block();
                clear();
                break;
            }
            if (GetAsyncKeyState(0x27)){ //right arrow
                right();
            }
            if (GetAsyncKeyState(0x25)){ //left arrow
                left();
            }
            if (GetAsyncKeyState(0x5a)){ //Z key
                right_rotate();
            }
            if (GetAsyncKeyState(0x58)){ //X key
                left_rotate();
            }
        }
    }
}

void Block::set_screen(char list[20][10]){
    for (int i{0}; i<20; ++i){
        for (int j{0}; j<10; ++j){
            screen[i][j] = list[i][j];
        }
    }
}

int main(){
    char array[20][10];
    for (int i{0}; i < 20; i++){
        for(int j{0}; j < 10; j++){
            array[i][j] = 249;
        }
    }
    Block current;
    current.set_screen(array);
    current.update();
    std::system("cls");
    printf("gg");
}