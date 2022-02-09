#include <stdio.h>
#include <time.h>
#include <windows.h>
#include <stdlib.h>

class Block{
    public:
    char pos[2];
    char px_pos[4][2];
    void down(char[20][10]);
    void right(char[20][10]);
    void left(char[20][10]);
    void create_block(char[20][10], int[7]);
    void create_positions(char[20][10]);
};

void Block::create_block(char l[20][10], int blocks[7]){
    srand(time(0));
    int count{0};
    int block{blocks[rand()%7]};
    for(int i{0}; i < 8; ++i){
        int px{(block >> i) & 1};
        if (px == 1){
            l[int(i/4)][(i%4)+3] = 219;
            px_pos[count][0] = (i%4)+3;
            px_pos[count][1] = int(i/4);
            count += 1;
        }
    }
}

// void Block::create_positions(char l[20][10]){
//     int count{0};
//     for(int y{pos[1]-3}; y < pos[1]+4; y++){
//         for(int x{0}; x < 10; x++){
//             if(l[y][x] == 219){
//                 px_pos[count][0] = x;
//                 px_pos[count][1] = y;
//                 count += 1;
//             }
//         }
//     }
// }

void Block::down(char l[20][10]){
    bool place{true};
    for(int i{0}; i < 4; i++){
        if (l[px_pos[i][1]+1][px_pos[i][0]] == 79 || px_pos[i][1]+1 > 19){
            place = false;
            break;
        }
    }
    if (place){
        for(int i{0}; i < 4; i++){
            l[px_pos[i][1]][px_pos[i][0]] = 249;
        }
        for(int i{0}; i < 4; i++){
            px_pos[i][1] += 1;
            l[px_pos[i][1]][px_pos[i][0]] = 219;
        }
    }
}

void Block::right(char l[20][10]){
    bool place{true};
    for(int i{0}; i < 4; i++){
        if (l[px_pos[i][1]][px_pos[i][0]+1] == 79 || px_pos[i][0]+1 > 9){
            place = false;
            break;
        }
    }
    if (place){
        for(int i{0}; i < 4; i++){
            l[px_pos[i][1]][px_pos[i][0]] = 249;
        }
        for(int i{0}; i < 4; i++){
            px_pos[i][0] += 1;
            l[px_pos[i][1]][px_pos[i][0]] = 219;
        }
    }
}


void Block::left(char l[20][10]){
    bool place{true};
    for(int i{0}; i < 4; i++){
        if (l[px_pos[i][1]][px_pos[i][0]-1] == 79 || px_pos[i][0]-1 < 0){
            place = false;
            break;
        }
    }
    if (place){
        for(int i{0}; i < 4; i++){
            l[px_pos[i][1]][px_pos[i][0]] = 249;
        }
        for(int i{0}; i < 4; i++){
            px_pos[i][0] -= 1;
            l[px_pos[i][1]][px_pos[i][0]] = 219;
        }
    }
}



void change_px(char l[20][10], char positions[4][2]){
    for(int i{0}; i < 4; i++){
        l[positions[i][1]][positions[i][0]] = 219;
    }
}
void render(char l[20][10]){
    for(int y{0}; y<20; y++){
        for(int x{0}; x<10; x++){
            printf("%c",l[y][x]);
        }
        printf("\n");
    }
}


int main(){
    while (1){   
    int BLOCKS[7] {78, 142, 198, 102, 108, 46, 15};
    char screen[20][10];
    for (int i{0}; i < 20; i++){
        for(int j{0}; j < 10; j++){
            screen[i][j] = 249;
        }
    }
    Block current;
    current.create_block(screen, BLOCKS);
    while(1){
        if (GetAsyncKeyState(0x28)){
            current.down(screen);
        }
        if (GetAsyncKeyState(0x27)){
            current.right(screen);
        }
        if (GetAsyncKeyState(0x25)){
            current.left(screen);
        }
        render(screen);
        std::system("cls");
        }
    }
}
