Player *
player_get(Game *game, PlayerID id)
{
    Player *result = NULL;
    result = &game->players[id-1];
    return(result);
}

void
match_reset(Match *match)
{
    match->status = match_status_playing;
    match->player_turn = i32_rand(player_x, player_o+1);
    match->player_win = player_null;

    mem_set(match->board.cell, player_null, sizeof(match->board.cell));
}

void
match_update(Match *match)
{
    struct Input_Mouse *mouse = &input.mice[0];
    Board *board = &match->board;

	//check if inside
	if(mouse->pos.x > board->pos.x && mouse->pos.x < board->pos.x + board->dim.x &&
	   mouse->pos.y > board->pos.y && mouse->pos.y < board->pos.y + board->dim.y)
	{
		u8 cell_x = (mouse->pos.x - board->pos.x) / board->cell_dim.x;
		u8 cell_y = (mouse->pos.y - board->pos.y) / board->cell_dim.y;

		u8 *cell = (u8 *)board;

		if(button_pressed(button_left))
		{
			if(!board->cell[cell_y][cell_x])
			{
				board->cell[cell_y][cell_x] = match->player_turn;

				++board->filled_count;

				if(match->player_turn == player_x) match->player_turn = player_o;
				else match->player_turn = player_x;
			}
		}
	}
}

void
game_init(Game *game)
{
    player_get(game, player_x)->color = VEC4_COLOR_RED;
    player_get(game, player_o)->color = VEC4_COLOR_BLUE;

    Match *match = &game->match;
    match_reset(match);

    Board *board = &match->board;
    board->cell_dim = VEC2(150, 150);
    board->dim = VEC2(board->cell_dim.x*3, board->cell_dim.y*3);
    board->pos = VEC2((os_context.dim.x/2) - (board->dim.x/2),
                      (os_context.dim.y/2) - (board->dim.y/2));
    board->color = VEC4_COLOR_WHITE;
}

void
game_draw(Game *game)
{
    Match *match = &game->match;

    /* Draw the background */
    Vec4 background_color = VEC4_ZERO;
    switch(match->status)
    {
        case match_status_playing: background_color = VEC4_COLOR_BLACK; break;
        case match_status_finished:
        {
            if(match->player_win == player_null) background_color = VEC4_COLOR_WHITE;
            else background_color = player_get(game, match->player_win)->color;
        }
    }
    gl_viewport_color_set(background_color);
    gl_viewport_color_clear();

    /* Draw the board */
    Board *board = &match->board;

    Vec2 end = VEC2(board->pos.x + board->dim.x, board->pos.y + board->dim.y);
    struct Rec2 rec = REC2(board->pos, end);
    struct Box2 box = box2_from_rec2(rec);
    //rec2_draw(&rec, color);
    box2_draw(&box, .5, board->color);

    for(i32 i = 0; i < 3; ++i)
    {
        for(i32 j = 0; j < 3; ++j)
        {
            f32 spacing = 10.;
            Vec2 cell_start = VEC2(board->pos.x + (j * board->cell_dim.x) + spacing,
                            board->pos.y + (i * board->cell_dim.y) + spacing);

			Vec2 cell_end = VEC2(board->pos.x + (j + 1) * board->cell_dim.x - spacing,
							 board->pos.y + (i + 1) * board->cell_dim.y - spacing);

			if (j > 0) cell_start.x -= spacing / 2;
			if (j < 2) cell_end.x += spacing / 2;
			if (i > 0) cell_start.y -= spacing / 2;
			if (i < 2) cell_end.y += spacing / 2;

            PlayerID cell_player = board->cell[i][j];

            Vec4 color;
            if(cell_player != player_null) color = player_get(game, cell_player)->color;
            else color = vec4_mf(VEC4_COLOR_WHITE, 0.5);

            rec = REC2(cell_start, cell_end);
            box = box2_from_rec2(rec);
            box2_draw(&box, 1.0, color);
        }
    }
}

void
game_update(Game *game)
{
    if(game->match.status == match_status_playing) match_update(&game->match);
    game_draw(game);
}