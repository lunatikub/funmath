#ifndef ANT_LANGTON_CFG_H_
# define ANT_LANGTON_CFG_H_

ant_trans_t cfg_1[] = {
    [__WHITE] = { __RR, RED   },
    [__RED]   = { __LR, GREEN },
    [__GREEN] = { __LR, WHITE },
};

ant_trans_t cfg_2[] = {
    [__WHITE]  = { __RR, RED },
    [__RED]    = { __LR, GREEN },
    [__GREEN]  = { __RR, SKY },
    [__SKY]    = { __RR, YELLOW },
    [__YELLOW] = { __RR, PURPLE },
    [__PURPLE] = { __RR, GREY },
    [__GREY]   = { __RR, DRED },
    [__DRED]   = { __LR, DGREEN },
    [__DGREEN] = { __LR, WHITE },
};

ant_trans_t cfg_3[] = {
    [__WHITE] = { __LR, BLACK },
    [__BLACK] = { __RR, WHITE },
};

#endif /* !ANT_LANGTON_CFG_H_ */
