/**/

/**
 * @uml.property  name="materialnumber" multiplicity="(0 -1)" dimension="2"
 */
int materialnumber[2][7] = { { 5, 2, 2, 2, 2, 2, 1 }, { 5, 2, 2, 2, 2, 2, 1 } };

#include "AIPlayer.h"


#include "ChoiDon.h"
#define COCOS2D_DEBUG 1
static AIPlayer m_SharedAIPlayer;

AIPlayer* AIPlayer::shared() {
	return &m_SharedAIPlayer;
}

AIPlayer::AIPlayer(void) {
	side = DARK;
	xside = LIGHT;
	m_Stop = true;
	setMaxPly(4);
}

void AIPlayer::setMaxPly(int sPly)
{
    switch (sPly) {
        case 1:
            MAX_PLY = 2;
            type = 0;
            break;
        case 2:
            MAX_PLY = 2;
            type = 0;
            break;
        case 3:
            MAX_PLY = 4;
            type = 0;
            break;
        case 4:
            MAX_PLY = 4;
            type = 0;
            break;
        case 5:
            MAX_PLY = 5;
            type = 0;
            break;
        case 6:
            MAX_PLY = 6;
            type = 0;
            break;
        case 7:
            MAX_PLY = 7;
            type = 1;
            break;
        case 8:
            MAX_PLY = 8;
            type = 0;
            break;
        case 9:
            MAX_PLY = 9;
            type = 1;
            break;
        case 10:
            MAX_PLY = 10;
            type = 0;
            break;
        default:
            MAX_PLY = 5;
            type = 0;
            break;
    }
}

static void* runThread(void* obj) {
	AIPlayer* player = reinterpret_cast<AIPlayer*>(obj);
	player->play();
    
	return NULL;
}

AIPlayer::~AIPlayer(void) {
}
Move mvtmp1;
Move mvtmp2;
void AIPlayer::start() {
    CCLOG("AI for side: %d", side);
	m_Stop = false;
    mvtmp1.from = mvtmp1.dest = mvtmp2.from = mvtmp2.dest = -1;
   // pthread_t m_thread1;
	pthread_create(&m_thread, NULL, &runThread, this);
   // pthread_create(&m_thread, NULL, &runThread, this);
}

void AIPlayer::stop() {
	if (!m_Stop) {
		m_Stop = true;
		int result = pthread_kill(m_thread, 0);
		CCLOG("cancel pthread result: %d", result);
	}
}
void AIPlayer::play() {
	gen_begin[0] = 0;
	ply = 0;
	hdp = 0;
	newmove.from = -1;
	newmove.dest = -1;
	int inf = INFINITY;
	for (int i = 1; i <= MAX_PLY; ++i) {
		AlphaBeta(-inf, inf, i);
		if (newmove.from == -1)
			break;
	}
	if (m_GameScene && !m_Stop) {
      //  int result = pthread_kill(m_thread, 0);//them
		/*GameScene* game = dynamic_cast<GameScene*>(m_GameScene);*/
     
        Move mv2;
         int i = randomx(100,0);
        if(i%2!=0 || mvtmp1.from == -1 || mvtmp1.dest == -1){
            mv2 = mvtmp2;
            
        }else mv2 = mvtmp1;
           mvtmp1.from = mvtmp1.dest = mvtmp2.from = mvtmp2.dest = -1;
        CCLOG("new move from AI: %d %d % d % d", newmove.from, newmove.dest,mv2.from,mv2.dest);
		//m_GameScene->AINewMove(newmove.from, newmove.dest);
         m_GameScene->AINewMove(mv2.from, mv2.dest);
        
        if (!m_Stop) {
            m_Stop = true;
            pthread_kill(m_thread, 0);
        }
	}
}
int AIPlayer::randomx(int max,int min)
{
    int k = CCUserDefault::sharedUserDefault()->getIntegerForKey("RAMDOM");
    k++;
    if(k==50){
        CCUserDefault::sharedUserDefault()->setIntegerForKey("RAMDOM",0);
    }else CCUserDefault::sharedUserDefault()->setIntegerForKey("RAMDOM",k);
    CCUserDefault::sharedUserDefault()->flush();
    int range = max-min - k;
    int actualx = (rand() % range)+min;
    return actualx;
}
void AIPlayer::setSide(int _side) {
	side = _side;
	xside = 1 - side;
    CCLOG("AI set new side: %d", _side);
}

void AIPlayer::movePiece(int from, int dest) {
	piece[dest] = piece[from];
	piece[from] = EMPTY;
	//
	color[dest] = color[from];
	color[from] = EMPTY;
}

int AIPlayer::AlphaBeta(int alpha, int beta, int depth) {
	int i, j, value, best;
	if (m_Stop) {
		return 0;
	}
	if (depth == 0)
		return Quiescence(alpha, beta);
    
	if (!Gen())
		return -1000 + ply;
	if (follow_pv)
		Check_pv();
	Sort();
	best = -INFINITY;
	pv_length[ply] = ply;
    
	for (i = gen_begin[ply]; i < gen_end[ply] && best < beta; i++) {
		if (best > alpha)
			alpha = best;
        
		if (MakeMove(gen_dat[i].m))
			value = 1000 - ply;
		else
			value = -AlphaBeta(-beta, -alpha, depth - 1);
		UnMakeMove();
        
		if (value > best) {
			history[gen_dat[i].m.from][gen_dat[i].m.dest] = depth;
			best = value;
			if (ply == 0)
				newmove = gen_dat[i].m;
            if (mvtmp2.from != newmove.from || mvtmp2.dest != newmove.dest) {
                // std::cout<<"truoc "<<mvtmp2.from<<"  "<<mvtmp2.dest<<"  "<<mvtmp1.from<<"  "<<mvtmp1.dest<<"  "<<std::endl;
                mvtmp1 = mvtmp2;
                mvtmp2 = newmove;
                // std::cout<<"sau "<<mvtmp2.from<<"  "<<mvtmp2.dest<<"  "<<mvtmp1.from<<"  "<<mvtmp1.dest<<"  "<<std::endl;
            }
            
			pv[ply][ply] = gen_dat[i].m;
            
          //  CCLog("pv_length[ply + 1] %i  ply %i",pv_length[ply + 1],ply);
            
			for (j = ply + 1; j < pv_length[ply + 1]; j++)
            {
				pv[ply][j] = pv[ply + 1][j];
              //   CCLog("j%i  ",j);
            }
			pv_length[ply] = pv_length[ply + 1];
		}
	}
    
	return best;
}

int AIPlayer::Quiescence(int alpha, int beta) {
	int i, j, value, best;
	if (m_Stop) {
		return 0;
	}
	value = Eval();
	if (value >= beta) {
		return value;
	}
	if (value > alpha)
		alpha = value;
    
	if (!GenCapture()) {
		if (!IsInCheck(side))
			return value;
		if (!Gen())
			return -1000 + ply;
	}
    
	if (follow_pv) {
		Check_pv();
	}
	Sort();
	best = -INFINITY;
	pv_length[ply] = ply;
    
	for (i = gen_begin[ply]; i < gen_end[ply] && best < beta; i++) {
		if (best > alpha)
			alpha = best;
        
		if (MakeMove(gen_dat[i].m))
			value = 1000 - ply;
		else
			value = -Quiescence(-beta, -alpha);
		UnMakeMove();
        
		if (value > best) {
			best = value;
			pv[ply][ply] = gen_dat[i].m;
			for (j = ply + 1; j < pv_length[ply + 1]; j++) {
			
                pv[ply][j] = pv[ply + 1][j];
			}
			pv_length[ply] = pv_length[ply + 1];
		}
	}
    
	return best;
}

void AIPlayer::Check_pv() {
	int i;
	for (follow_pv = false, i = gen_begin[ply]; i < gen_end[ply]; i++) {
		if (gen_dat[i].m.from == pv[0][ply].from
            && gen_dat[i].m.dest == pv[0][ply].dest) {
			follow_pv = true;
			gen_dat[i].prior += 1000;
			return;
		}
	}
}

void AIPlayer::Sort() {
	Quicksort(gen_begin[ply], gen_end[ply] - 1);
}

void AIPlayer::Quicksort(int q, int r) {
	int i, j, x;
	gen_rec g;
	i = q;
	j = r;
	x = gen_dat[(q + r) / 2].prior;
	do {
		while (gen_dat[i].prior > x)
			i++;
		while (gen_dat[j].prior < x)
			j--;
		if (i <= j) {
			g = gen_dat[i];
			gen_dat[i] = gen_dat[j];
			gen_dat[j] = g;
			i++;
			j--;
		}
	} while (i <= j);
	if (q < j)
		Quicksort(q, j);
	if (i < r)
		Quicksort(i, r);
}
/**/

void AIPlayer::LoadBoard(int piece1[], int color1[]) {
	/*Create board*/
	for (int i = 0; i < BOARD_SIZE; i++) {
		piece[i] = piece1[i];
		color[i] = color1[i];
		//CCLOG("piece: %d color: %d", piece[i], color[i]);
	}
}

bool AIPlayer::MakeMove(Move m) {
	int from, dest, p;
	from = m.from;
	dest = m.dest;
	p = piece[dest];
	if (p != EMPTY)
		materialnumber[xside][p]--;
	hist_dat[hdp].m = m;
	hist_dat[hdp].capture = p;
	piece[dest] = piece[from];
	piece[from] = EMPTY;
	color[dest] = color[from];
	color[from] = EMPTY;
	hdp++;
	ply++;
	side = xside;
	xside = 1 - xside;
	return p == KING;
}

void AIPlayer::UnMakeMove() {
	int from, dest;
	hdp--;
	ply--;
	side = xside;
	xside = 1 - xside;
	from = hist_dat[hdp].m.from;
	dest = hist_dat[hdp].m.dest;
	piece[from] = piece[dest];
	color[from] = color[dest];
	piece[dest] = hist_dat[hdp].capture;
	if (piece[dest] == EMPTY)
		color[dest] = EMPTY;
	else
		color[dest] = xside;
	if (piece[dest] != EMPTY)
		materialnumber[xside][piece[dest]]++;
}

bool AIPlayer::Gen() {
	int i, j, k, n, p, x, y, t, fcannon;
	gen_end[ply] = gen_begin[ply];
	//CCLOG("gen begin: %d ply: %d", gen_begin[ply], ply);
	for (i = 0; i < BOARD_SIZE; i++)
		if (color[i] == side) {
			//CCLOG("side: %d color: %d", side, color[i]);
			p = piece[i];
			for (j = 0; j < 8; j++) {
				if (offset[p][j] == 0)
					break;
				x = mailbox90[i];
				fcannon = 0;
				if (p == ROOK || p == CANNON)
					n = 9;
				else
					n = 1;
				for (k = 0; k < n; k++) {
					if (p == PAWN && side == LIGHT)
						x -= offset[p][j];
					else
						x += offset[p][j];
                    
					y = mailbox182[x];
					if (side == DARK)
						t = y;
					else
						t = 89 - y;
					if (y == -1 || (legalposition[t] & maskpiece[p]) == 0)
						break;
					if (fcannon == 0) {
						if (color[y] != side)
							switch (p) {
                                case KNIGHT:
                                    if (color[i + knightcheck[j]] == EMPTY)
                                        Gen_push(i, y);
                                    break;
                                case ELEPHAN:
                                    if (color[i + elephancheck[j]] == EMPTY)
                                        Gen_push(i, y);
                                    break;
                                case CANNON:
                                    if (color[y] == EMPTY)
                                        Gen_push(i, y);
                                    break;
                                default:
                                    Gen_push(i, y);
							}
						if (color[y] != EMPTY) {
							if (p == CANNON)
								fcannon++;
							else
								break;
						}
					} else { /* CANNON switch */
						if (color[y] != EMPTY) {
							if (color[y] == xside)
								Gen_push(i, y);
							break;
						}
					}
				} /* for k */
			} /* for j */
		}
    
	gen_end[ply + 1] = gen_end[ply];
	gen_begin[ply + 1] = gen_end[ply];
	//brandtotal += gen_end[ply] - gen_begin[ply]; gencount++;
	return (gen_end[ply] > gen_begin[ply]);
}

void AIPlayer::AILog() {
	CCLOG("ply: %d gen: %d", ply, gen_end[ply]-gen_begin[ply]);
}

int* AIPlayer::getAllAvaiblePos(int pos) {
	int* aMove = new int[20];
	int count = 0;
	int _side = color[pos];
	int p = piece[pos];
	int _xside = (1 - _side);
    //	CCLOG("piece: %d color: %d", p, _side);
	int n, x, y, fcannon, t;
	for (int j = 0; j < 8; j++) {
		if (offset[p][j] == 0)
			break;
		x = mailbox90[pos];
		fcannon = 0;
		if (p == ROOK || p == CANNON)
			n = 9;
		else
			n = 1;
		for (int k = 0; k < n; k++) {
			if (p == PAWN && _side == LIGHT)
				x -= offset[p][j];
			else
				x += offset[p][j];
            
			y = mailbox182[x];
			if (_side == DARK)
				t = y;
			else
				t = 89 - y;
			if (y == -1 || (legalposition[t] & maskpiece[p]) == 0)
				break;
			if (fcannon == 0) {
				if (color[y] != _side)
					switch (p) {
                        case KNIGHT:
                            if (color[pos + knightcheck[j]] == EMPTY
								&& MoveSave(pos, y))
                                aMove[count++] = y;
                            break;
                        case ELEPHAN:
                            if (color[pos + elephancheck[j]] == EMPTY
								&& MoveSave(pos, y))
                                aMove[count++] = y;
                            break;
                        case CANNON:
                            if (color[y] == EMPTY && MoveSave(pos, y))
                                aMove[count++] = y;
                            break;
                        default:
                            if (MoveSave(pos, y))
                                aMove[count++] = y;
					}
				if (color[y] != EMPTY) {
					if (p == CANNON)
						fcannon++;
					else
						break;
				}
			} else { /* CANNON switch */
				if (color[y] != EMPTY) {
					if (color[y] == _xside && MoveSave(pos, y))
						aMove[count++] = y;
					break;
				}
			}
		} /* for k */
	} /* for j */
    //	CCLOG("count: %d", count);
	aMove[count] = -1;
    
	return aMove;
}

void AIPlayer::Gen_push(int from, int dest) {
	if (MoveSave(from, dest)) {
		if (color[from] != side)
			return;
		gen_dat[gen_end[ply]].m.from = from;
		gen_dat[gen_end[ply]].m.dest = dest;
		if (piece[dest] != EMPTY)
			gen_dat[gen_end[ply]].prior = (piece[dest] + 1) * 100 - piece[from];
		else
			gen_dat[gen_end[ply]].prior = history[from][dest];
		gen_end[ply]++;
	}
}

bool AIPlayer::GenCapture() {
	int i, j, k, n, p, x, y, t, fcannon;
    
	gen_end[ply] = gen_begin[ply];
    
	for (i = 0; i < BOARD_SIZE; i++)
		if (color[i] == side) {
			p = piece[i];
			for (j = 0; j < 8; j++) {
				if (offset[p][j] == 0)
					break;
				x = mailbox90[i];
				fcannon = 0;
                
				if (p == ROOK || p == CANNON)
					n = 9;
				else
					n = 1;
				for (k = 0; k < n; k++) {
					if (p == PAWN && side == LIGHT)
						x -= offset[p][j];
					else
						x += offset[p][j];
                    
					y = mailbox182[x];
					if (side == DARK)
						t = y;
					else
						t = 89 - y;
					if (y == -1 || (legalposition[t] & maskpiece[p]) == 0)
						break;
					if (fcannon == 0) {
						if (color[y] != side) {
							switch (p) {
                                case KNIGHT:
                                    if (color[i + knightcheck[j]] == EMPTY
										&& color[y] == xside)
                                        Gen_push(i, y);
                                    break;
                                case ELEPHAN:
                                    if (color[i + elephancheck[j]] == EMPTY
										&& color[y] == xside)
                                        Gen_push(i, y);
                                    break;
                                case CANNON:
                                    break;
                                default:
                                    if (color[y] == xside)
                                        Gen_push(i, y);
							}
						}
						if (color[y] != EMPTY) {
							if (p == CANNON)
								fcannon = 1;
							else
								break;
						}
					} else { /* CANNON switch */
						if (color[y] != EMPTY) {
							if (color[y] == xside)
								Gen_push(i, y);
							break;
						}
					}
				} /* for k */
			} /* for j */
		}
	gen_end[ply + 1] = gen_end[ply];
	gen_begin[ply + 1] = gen_end[ply];
    
	//		capbrandtotal += (unsigned long)gen_end[ply] - gen_begin[ply];
	//		if (gen_end[ply] > gen_begin[ply]) capgencount++;
	return (gen_begin[ply] < gen_end[ply]);
}

bool AIPlayer::MoveSave(int from, int dest) {
	Move ms;
	bool k;
    
	if (piece[dest] == KING)
		return true;
    
	ms.from = from;
	ms.dest = dest;
	MakeMove(ms);
	//nodecount--;
    if (color[dest] == EMPTY) {
        return false;
    }
	k = isKingSafe(color[dest]);
	UnMakeMove();
	return k;
}

bool AIPlayer::IsInCheck(int xside2) {
	return Attack(getKingPosition(xside2), xside2);
}

bool AIPlayer::isKingSafe(int _side) {
	int pos = getKingPosition(_side);
	return !(Attack(pos, _side) || IsKingFace(pos));
}

int AIPlayer::getKingPosition(int _side) {
	int i = 0, pos;
	do {
        if (_side > 1 || i > 8)
        {
            break;
        }
		pos = kingpalace[_side][i];
		i++;
	} while (piece[pos] != KING);
	return pos;
}
bool AIPlayer::IsKingFace(int pos) {
	int k, p = pos;
	if (color[pos] == DARK) {
		k = 9;
	} else {
		k = -9;
	}
	for (int i = 0; i < 10; ++i) {
		p += k;
		if (p < 0 || p > 89) {
			break;
		}
		if (piece[p] != EMPTY && piece[p] != KING) {
			return false;
		} else if (piece[p] == KING) {
			return true;
		}
	}
	return false;
    
}

bool AIPlayer::Attack(int pos, int side) {
	int j, k, x, y, fcannon, sd, xsd;
    
	sd = side;
	xsd = 1 - sd;
    
	for (j = 0; j < 4; j++) {			// ROOK, CANNON, PAWN, KING
		x = mailbox90[pos];
		fcannon = 0;
		for (k = 0; k < 9; k++) {
			x = x + offset[ROOK][j];
			y = mailbox182[x];
			if (y == -1)
				break;
			if (fcannon == 0) {
				if (color[y] == xsd)
					switch (piece[y]) {
                        case ROOK:
                            return true;
                        case KING:
                            if (piece[pos] == KING) {
                                return true;
                            }
                            break;
                        case PAWN:
                            if (k == 0
								&& ((sd == DARK && j != 2)
                                    || (sd == LIGHT && j != 3)))
                                return true;
					}
				if (color[y] != EMPTY)
					fcannon = 1;
			} else
                if (color[y] != EMPTY) {
                    if (color[y] == xsd && piece[y] == CANNON)
                        return true;
                    break;
                }
		} // for k
	} // for j
    
	for (j = 0; j < 8; j++) {				// Knight Check
		y = mailbox182[mailbox90[pos] + offset[KNIGHT][j]];
		if (y == -1)
			continue;
		if (color[y]
            == xsd&& piece[y]==KNIGHT && color[pos+knightcheck2[j]]==EMPTY)
            return true;
	}
	return false;
}

int* AIPlayer::getAttackPosForSide(int _side)
{
    int j, k, x, y, fcannon, sd, xsd;
    int pos = getKingPosition(_side);
    int* result = new int[5];
    int i = 0;
	sd = _side;
	xsd = 1 - sd;
    
	for (j = 0; j < 4; j++) {			// ROOK, CANNON, PAWN, KING
		x = mailbox90[pos];
		fcannon = 0;
		for (k = 0; k < 9; k++) {
			x = x + offset[ROOK][j];
			y = mailbox182[x];
			if (y == -1)
				break;
			if (fcannon == 0) {
				if (color[y] == xsd)
					switch (piece[y]) {
                        case ROOK:
                            result[i++] = y;
                            break;
                        case KING:
                            if (piece[pos] == KING) {
                                result[i++] = y;
                            }
                            break;
                        case PAWN:
                            if (k == 0
								&& ((sd == DARK && j != 2)
                                    || (sd == LIGHT && j != 3)))
                                result[i++] = y;
                            break;
					}
				if (color[y] != EMPTY)
					fcannon = 1;
			} else
                if (color[y] != EMPTY) {
                    if (color[y] == xsd && piece[y] == CANNON)
                        result[i++] = y;
                    break;
                }
		} // for k
	} // for j
    
	for (j = 0; j < 8; j++) {				// Knight Check
        x = mailbox90[pos];
		y = mailbox182[x + offset[KNIGHT][j]];
		if (y == -1)
			continue;
		if (color[y]
            == xsd&& piece[y]==KNIGHT && color[pos+knightcheck2[j]]==EMPTY)
            result[i++] = y;
	}
    
    for (; i < 5; ++i) {
        result[i] = -1;
    }
    
	return result;
}

int AIPlayer::Eval() {
	int i, s = 0;
	for (i = 0; i < BOARD_SIZE; i++) {
		if (color[i] == DARK)
			s += pointtable[type][piece[i]][DARK][i];
		else if (color[i] == LIGHT)
			s -= pointtable[type][piece[i]][LIGHT][i];
	}
	if (side == LIGHT)
		s = -s;
    
    if (type) {
        return s;
    }
	return s + Bonous();
}

int AIPlayer::Bonous() {
	int i, s, bn[2][7] = { { -2, -3, -3, -4, -4, -5, 0 }, { -2, -3, -3, -4, -4,
        -5, 0 } };
	for (i = 0; i < 2; i++) {			// Scan DARK and LIGHT
		if (materialnumber[i][BISHOP] < 2) {
			bn[1 - i][ROOK] += 4;
			bn[1 - i][KNIGHT] += 2;
			bn[1 - i][PAWN] += 1;
		}
		if (materialnumber[i][ELEPHAN] < 2) {
			bn[1 - i][ROOK] += 2;
			bn[1 - i][CANNON] += 2;
			bn[1 - i][PAWN] += 1;
		}
	}
	if (color[0] == DARK && color[1] == DARK && piece[0] == ROOK
        && piece[1] == KNIGHT)
		bn[DARK][6] -= 10;
	if (color[7] == DARK && color[8] == DARK && piece[8] == ROOK
        && piece[7] == KNIGHT)
		bn[DARK][6] -= 10;
	if (color[81] == LIGHT && color[82] == LIGHT && piece[81] == ROOK
        && piece[82] == KNIGHT)
		bn[LIGHT][6] -= 10;
	if (color[88] == LIGHT && color[89] == LIGHT && piece[89] == ROOK
        && piece[88] == KNIGHT)
		bn[LIGHT][6] -= 10;
    
	s = (bn[side][6] - bn[xside][6]);
    
	for (i = 0; i < 6; i++)
		s += materialnumber[side][i] * bn[side][i]
        - materialnumber[xside][i] * bn[xside][i];
	return s;
}
