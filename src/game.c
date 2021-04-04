void
match_reset(Match *match)
{
    match->status = match_status_playing;
    match->turn = i32_rand(player_o, player_x);
    match->winner = player_null;

    mem_set(match->board.cell, player_null, sizeof(match->board.cell));
}

void
match_update(Match *match)
{
}

void
match_draw(Match *match)
{
    Board *board = &match->board;

    Vec4 color = VEC4_COLOR_RED;
    Vec2 end = VEC2(board->pos.x + board->dim.x, board->pos.y + board->dim.y);
    struct Rec2 rec = REC2(board->pos, end);
    rec2_draw(&rec, color);
}

void
game_init(Game *game)
{
    game->players[player_x].color = VEC4_COLOR_RED;
    game->players[player_o].color = VEC4_COLOR_BLUE;

    Match *match = &game->match;
    match_reset(match);

    Board *board = &match->board;
    board->cell_dim = VEC2(150, 150);
    board->dim = VEC2(board->cell_dim.x*3, board->cell_dim.y*3);
    board->pos = VEC2((os_context.dim.x/2) - (board->dim.x/2),
                      (os_context.dim.y/2) - (board->dim.y/2));
}

void
game_draw(Game *game)
{
    Match *match = &game->match;

    Vec4 background_color = VEC4_ZERO;
    switch(match->status)
    {
        case match_status_playing: background_color = VEC4_COLOR_BLACK; break;
        case match_status_finished:
        {
            if(match->winner == player_null) background_color = VEC4_COLOR_WHITE;
            else background_color = game->players[match->winner].color;
        }
    }
    //gl_viewport_color_set(background_color);
    //gl_viewport_color_clear();

    match_draw(match);
}

void
game_update(Game *game)
{
    if(game->match.status == match_status_playing) match_update(&game->match);
    game_draw(game);
}