typedef enum PlayerID
{
    player_null,
    player_x,
    player_o,
} PlayerID;

typedef struct Player
{
    Vec4 color;
} Player;

typedef struct Board
{
    Vec2 pos;
    Vec2 dim;
    Vec4 color;

    PlayerID cell[3][3];
    Vec2 cell_dim;

    u32 filled_count;
} Board;

typedef enum MatchStatus
{
    match_status_playing,
    match_status_finished,
} MatchStatus;

typedef struct Match
{
    Board board;
    MatchStatus status;

    PlayerID player_turn;
    PlayerID player_win;
} Match;

typedef struct Game
{
    Player players[2];
    Match match;

    bool running;
} Game;