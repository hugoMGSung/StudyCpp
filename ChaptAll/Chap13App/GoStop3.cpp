#include <stdio.h>
#include <conio.h>
#include <string.h>
#include "cursor.h"
#include <assert.h>
#include <iostream>
using namespace std;

const int MaxCard = 48;
const int CardGap = 4;
const int Speed = 0;
const int PromptSpeed = 0;

// ȭ�� ������ ǥ���ϴ� Ŭ����
struct SCard
{
	char Name[4];
	SCard() { Name[0] = 0; }
	SCard(const char* pName) {
		strcpy(Name, pName);
	}
	int GetNumber() const {
		if (isdigit(Name[0])) return Name[0] - '0';
		if (Name[0] == 'J') return 10;
		if (Name[0] == 'D') return 11;
		return 12;
	};
	int GetKind() const {
		if (strcmp(Name + 1, "��") == 0) return 0;
		else if (strcmp(Name + 1, "��") == 0) return 1;
		else if (strcmp(Name + 1, "��") == 0) return 2;
		else if (strcmp(Name + 1, "��") == 0) return 3;
		else return 4;
	}
	friend ostream& operator <<(ostream& c, const SCard& C) {
		return c << C.Name;
	}
	bool operator ==(const SCard& Other) const {
		return (strcmp(Name, Other.Name) == 0);
	}
	bool operator <(const SCard& Other) const {
		if (GetNumber() < Other.GetNumber()) return true;
		if (GetNumber() > Other.GetNumber()) return false;
		if (GetKind() < Other.GetKind()) return true;
		return false;
	}
};

// ȭ���� �ʱ� ī�� ���
SCard HwaToo[MaxCard] = {
	"1��","1��","1��","1��","2��","2��","2��","2��","3��","3��","3��","3��",
	"4��","4��","4��","4��","5��","5��","5��","5��","6��","6��","6��","6��",
	"7��","7��","7��","7��","8��","8��","8��","8��","9��","9��","9��","9��",
	"J��","J��","J��","J��","D��","D��","D��","D��","B��","B��","B��","B��"
};

// ī���� ������ �����ϴ� Ŭ����
class CCardSet
{
protected:
	SCard Card[MaxCard];
	int Num;
	const int sx, sy;
	CCardSet(int asx, int asy) : sx(asx), sy(asy) { Num = 0; }

public:
	int GetNum() { return Num; }
	SCard GetCard(int idx) { return Card[idx]; }
	void Reset() {
		for (int i = 0; i < MaxCard; i++) Card[i].Name[0] = 0;
		Num = 0;
	}
	void InsertCard(SCard C);
	SCard RemoveCard(int idx);
	int FindSameCard(SCard C, int* pSame);
	int FindFirstCard(const char* pName);
	int GetMaxSeries();
};

void CCardSet::InsertCard(SCard C) {
	int i;

	if (C.Name[0] == 0) return;
	for (i = 0; i < Num; i++) {
		if (C < Card[i]) break;
	}
	memmove(&Card[i + 1], &Card[i], sizeof(SCard) * (Num - i));
	Card[i] = C;
	Num++;
}

SCard CCardSet::RemoveCard(int idx) {
	assert(idx < Num);
	SCard C = Card[idx];
	memmove(&Card[idx], &Card[idx + 1], sizeof(SCard) * (Num - idx - 1));
	Num--;
	return C;
}

int CCardSet::FindSameCard(SCard C, int* pSame) {
	int i, num;
	int* p = pSame;

	for (i = 0, num = 0; i < Num; i++) {
		if (Card[i].GetNumber() == C.GetNumber()) {
			num++;
			*p++ = i;
		}
	}
	*p = -1;
	return num;
}

int CCardSet::FindFirstCard(const char* pName) {
	int i;

	for (i = 0; i < Num; i++) {
		if (strstr(Card[i].Name, pName) != NULL) {
			return i;
		}
	}
	return -1;
}

int CCardSet::GetMaxSeries() {
	int i, n, m, old = -1;

	for (i = 0, n = 1, m = 1; i < Num; i++) {
		if (old == Card[i].GetNumber()) {
			n++;
			m = max(n, m);
		}
		else {
			n = 1;
			old = Card[i].GetNumber();
		}
	}
	return m;
}

// ��� �߾ӿ� ī�带 �׾� ���� ��ũ
class CDeck : public CCardSet
{
public:
	CDeck(int asx, int asy) : CCardSet(asx, asy) { ; }
	void Shuffle() {
		int i, n;
		for (i = 0; i < MaxCard; i++) {
			do {
				n = random(MaxCard);
			} while (Card[n].Name[0] != NULL);
			Card[n] = HwaToo[i];
			Num++;
		}
	}
	SCard Pop() { return RemoveCard(Num - 1); }
	bool IsEmpty() { return Num == 0; }
	bool IsNotLast() { return Num > 1; }
	void Draw(bool bFlip) {
		gotoxy(sx, sy);
		cout << "??? " << (bFlip ? Card[Num - 1].Name : "   ");
	}
};

// ������ �ϴ� �÷��̾�
class CPlayer : public CCardSet
{
public:
	CPlayer(int asx, int asy) : CCardSet(asx, asy) { ; }
	void Draw(bool MyTurn) {
		int i, x;
		for (i = 0, x = sx; i < Num; i++, x += CardGap) {
			gotoxy(x, sy);
			cout << Card[i];
			if (MyTurn) {
				gotoxy(x, sy + 1);
				cout << '[' << i + 1 << ']';
			}
		}
	}
};

// ������ ����Ǵ� ���
class CBlanket : public CPlayer
{
public:
	CBlanket(int asx, int asy) : CPlayer(asx, asy) { ; }
	void Draw() {
		CPlayer::Draw(false);
	}
	void DrawSelNum(int* pSame) {
		int n;
		int* p;
		for (n = 1, p = pSame; *p != -1; p++, n++) {
			gotoxy(sx + *p * CardGap, sy - 1);
			cout << '[' << n << ']';
		}
	}
	void DrawTempCard(int idx, SCard C) {
		gotoxy(sx + idx * CardGap, sy + 1);
		cout << C;
	}
};

// �÷��̾ ���� ī���� ����
class CPlayerPae : public CCardSet
{
private:
	int nGo;

public:
	int OldScore;
	int bShake;
	CPlayerPae(int asx, int asy) : CCardSet(asx, asy) { OldScore = 6; nGo = 0; bShake = false; }
	void Reset() { CCardSet::Reset(); OldScore = 6; nGo = 0; bShake = false; }
	int GetGo() { return nGo; }
	void IncreaseGo() { nGo++; }
	void Draw();
	int RemovePee(int n, SCard* pCard);
	int CalcScore();
};

void CPlayerPae::Draw() {
	int i, kind;
	int x[4] = { sx,sx,sx,sx }, py = sy + 3;

	for (i = 0; i < Num; i++) {
		kind = Card[i].GetKind();
		if (kind < 3) {
			gotoxy(x[kind], sy + kind);
			x[kind] += CardGap;
		}
		else {
			gotoxy(x[3], py);
			x[3] += CardGap;
			if (x[3] > 75) {
				x[3] = sx;
				py++;
			}
		}
		cout << Card[i];
	}
	gotoxy(sx + 20, sy);
	cout << "����:" << CalcScore() << "��, " << nGo << "�� "
		<< (bShake ? "���" : "");
}

int CPlayerPae::RemovePee(int n, SCard* pCard) {
	int ns = 0, np = 0, tp;
	int i, idx, num = 0;
	SCard* p = pCard;

	for (i = 0; i < Num; i++) {
		if (Card[i].GetKind() == 3) ns++;
		if (Card[i].GetKind() == 4) np++;
	}
	tp = ns + np;
	if (tp == 0) return 0;

	switch (n) {
	case 1:
		if (np != 0) {
			*p++ = RemoveCard(FindFirstCard("��"));
			return 1;
		}
		else {
			*p++ = RemoveCard(FindFirstCard("��"));
			return 1;
		}
		break;
	case 2:
		if (ns != 0) {
			*p = RemoveCard(FindFirstCard("��"));
			return 1;
		}
		else {
			*p++ = RemoveCard(FindFirstCard("��"));
			num = 1;
			if (np >= 2) {
				*p++ = RemoveCard(FindFirstCard("��"));
				num = 2;
			}
			return num;
		}
	case 3:
		i = RemovePee(2, p);
		p += i;
		idx = RemovePee(1, p);
		return i + idx;
	default:
		return 0;
	}
}

int CPlayerPae::CalcScore() {
	int i, kind, n[4] = { 0, };
	int NewScore;
	static int gscore[] = { 0,0,0,3,4,15 };

	for (i = 0; i < Num; i++) {
		kind = Card[i].GetKind();
		if (kind == 3) n[kind]++;
		if (kind >= 3) kind = 3;
		n[kind]++;
	}
	NewScore = gscore[n[0]];
	if (n[0] == 3 && FindFirstCard("B��") != -1) NewScore--;
	if (n[1] >= 5) NewScore += (n[1] - 4);
	if (n[2] >= 5) NewScore += (n[2] - 4);
	if (n[3] >= 10) NewScore += (n[3] - 9);
	if (FindFirstCard("8��") != -1 && FindFirstCard("5��") != -1 && FindFirstCard("2��") != -1) NewScore += 5;
	if (FindFirstCard("1��") != -1 && FindFirstCard("2��") != -1 && FindFirstCard("3��") != -1) NewScore += 3;
	if (FindFirstCard("4��") != -1 && FindFirstCard("5��") != -1 && FindFirstCard("7��") != -1) NewScore += 3;
	if (FindFirstCard("9��") != -1 && FindFirstCard("J��") != -1 && FindFirstCard("6��") != -1) NewScore += 3;
	return NewScore;
}

// �Լ� ����
void Initialize();
void DrawScreen();
void OutPrompt(const char* Mes, int Wait = 0);
int InputInt(const char* Mes, int start, int end);

// ���� ����
CDeck Deck(18, 9);
CPlayer South(5, 20), North(5, 1);
CBlanket Blanket(5, 12);
CPlayerPae SouthPae(40, 14), NorthPae(40, 4);
bool SouthTurn;

// ���α׷��� �������ϴ� main �Լ�
void main()
{
	int i, ch;
	int arSame[4], SameNum;
	char Mes[256];
	CPlayer* Turn;
	CPlayerPae* TurnPae, * OtherPae;
	int UserIdx, UserSel, DeckSel;
	SCard UserCard, DeckCard;
	bool UserTriple, DeckTriple;
	int nSnatch;
	int NewScore;
	SCard arPee[3];
	int nPee;
	CPlayer* LastGo = NULL;

	randomize();
	for (int k = 0; k < 1000; k++) {
		srand(k);
		Initialize();
		DrawScreen();
		if (South.GetMaxSeries() == 3) {
			ch = InputInt("���� ī�尡 �� ���Դϴ�. (1:����, 2:�׳� �ϱ�) ", 1, 2);
			if (ch == 1) SouthPae.bShake = true;
		}
		if (North.GetMaxSeries() == 3) {
			ch = InputInt("���� ī�尡 �� ���Դϴ�. (1:����, 2:�׳� �ϱ�) ", 1, 2);
			if (ch == 1) NorthPae.bShake = true;
		}
		for (SouthTurn = true; !Deck.IsEmpty(); SouthTurn = !SouthTurn) {
			DrawScreen();
			if (SouthTurn) {
				Turn = &South;
				TurnPae = &SouthPae;
				OtherPae = &NorthPae;
			}
			else {
				Turn = &North;
				TurnPae = &NorthPae;
				OtherPae = &SouthPae;
			}

			sprintf(Mes, "���� ���� ȭ���� �����ϼ���(1~%d,0:����) ", Turn->GetNum());
			ch = InputInt(Mes, 0, Turn->GetNum());
			if (ch == 0) {
				if (InputInt("���� �����̴ϱ�?(0:��,1:�ƴϿ�)", 0, 1) == 0)
					return;
				else
					continue;
			}

			// �÷��̾ ī�带 ���� ����.
			UserTriple = DeckTriple = false;
			UserIdx = ch - 1;
			UserCard = Turn->GetCard(UserIdx);
			SameNum = Blanket.FindSameCard(UserCard, arSame);
			switch (SameNum) {
			case 0:
				UserSel = -1;
				Blanket.InsertCard(Turn->RemoveCard(UserIdx));
				DrawScreen();
				break;
			case 1:
				UserSel = arSame[0];
				break;
			case 2:
				if (Blanket.GetCard(arSame[0]) == Blanket.GetCard(arSame[1])) {
					UserSel = arSame[0];
				}
				else {
					Blanket.DrawSelNum(arSame);
					sprintf(Mes, "� ī�带 �����Ͻðڽ��ϱ�?(1~%d)", SameNum);
					UserSel = arSame[InputInt(Mes, 1, SameNum) - 1];
				}
				break;
			case 3:
				UserSel = arSame[1];
				UserTriple = true;
				break;
			}
			if (UserSel != -1) {
				Blanket.DrawTempCard(UserSel, UserCard);
			}
			delay(Speed);

			// ��ũ���� ������ �����´�.
			Deck.Draw(true);
			delay(Speed);
			DeckCard = Deck.Pop();
			SameNum = Blanket.FindSameCard(DeckCard, arSame);
			switch (SameNum) {
			case 0:
				DeckSel = -1;
				break;
			case 1:
				DeckSel = arSame[0];
				if (DeckSel == UserSel) {
					if (Deck.IsNotLast()) {
						Blanket.InsertCard(DeckCard);
						Blanket.InsertCard(Turn->RemoveCard(UserIdx));
						OutPrompt("�����߽��ϴ�.", PromptSpeed);
						continue;
					}
					else {
						DeckSel = -1;
					}
				}
				break;
			case 2:
				if (UserSel == arSame[0]) {
					DeckSel = arSame[1];
				}
				else if (UserSel == arSame[1]) {
					DeckSel = arSame[0];
				}
				else {
					if (Blanket.GetCard(arSame[0]) == Blanket.GetCard(arSame[1])) {
						DeckSel = arSame[0];
					}
					else {
						Blanket.DrawSelNum(arSame);
						sprintf(Mes, "� ī�带 �����Ͻðڽ��ϱ�?(1~%d)", SameNum);
						DeckSel = arSame[InputInt(Mes, 1, SameNum) - 1];
					}
				}
				break;
			case 3:
				DeckSel = arSame[1];
				DeckTriple = true;
				break;
			}
			if (DeckSel != -1) {
				Blanket.DrawTempCard(DeckSel, DeckCard);
			}
			Deck.Draw(false);
			delay(Speed);

			// ��ġ�ϴ� ī�带 �ŵ� ���δ�. �� ���� ���� ���� ���� ���� �´�.
			if (UserSel != -1) {
				if (UserTriple) {
					for (i = 0; i < 3; i++) {
						TurnPae->InsertCard(Blanket.RemoveCard(UserSel - 1));
					}
				}
				else {
					TurnPae->InsertCard(Blanket.RemoveCard(UserSel));
				}
				TurnPae->InsertCard(Turn->RemoveCard(UserIdx));
				if (DeckSel != -1 && DeckSel > UserSel) {
					DeckSel -= (UserTriple ? 3 : 1);
				}
			}
			if (DeckSel != -1) {
				if (DeckTriple) {
					for (i = 0; i < 3; i++) {
						TurnPae->InsertCard(Blanket.RemoveCard(DeckSel - 1));
					}
				}
				else {
					TurnPae->InsertCard(Blanket.RemoveCard(DeckSel));
				}
				TurnPae->InsertCard(DeckCard);
			}
			else {
				Blanket.InsertCard(DeckCard);
			}

			// ��, ����, �Ͼ��� ������ �����ϰ� ������ �Ǹ� ���´�.
			nSnatch = 0;
			if (Deck.IsNotLast()) {
				if (UserSel == -1 && SameNum == 1 && DeckCard.GetNumber() == UserCard.GetNumber()) {
					nSnatch++;
					OutPrompt("���Դϴ�.", PromptSpeed);
				}
				if (UserSel != -1 && SameNum == 2 && DeckCard.GetNumber() == UserCard.GetNumber()) {
					nSnatch++;
					OutPrompt("�����Դϴ�.", PromptSpeed);
				}
				if (Blanket.GetNum() == 0) {
					nSnatch++;
					OutPrompt("�Ͼ����Դϴ�.", PromptSpeed);
				}
				if (UserTriple || DeckTriple) {
					OutPrompt("�Ѳ����� �� ���� �Ծ����ϴ�.", PromptSpeed);
					nSnatch += UserTriple + DeckTriple;
				}
			}
			nPee = OtherPae->RemovePee(nSnatch, arPee);
			for (i = 0; i < nPee; i++) {
				TurnPae->InsertCard(arPee[i]);
			}

			// ������ ����ϰ� ��, ���� ���θ� �����Ѵ�.
			NewScore = TurnPae->CalcScore();
			if (Deck.IsNotLast() && NewScore > TurnPae->OldScore) {
				DrawScreen();
				if (InputInt("�߰� ������ ȹ���߽��ϴ�.(0:����, 1:���)", 0, 1) == 1) {
					TurnPae->OldScore = NewScore;
					TurnPae->IncreaseGo();
					LastGo = Turn;
				}
				else {
					break;
				}
			}
		}
		DrawScreen();

		// �ºο� �ǹ�, ����, ���� ���θ� �����Ѵ�.
		bool SouthWin;
		int SouthScore, NorthScore;
		int TurnPee = 0, TurnLight = 0, OtherPee = 0, OtherLight = 0;

		if (Deck.IsEmpty()) {
			if (LastGo != NULL) {
				SouthWin = (LastGo == &North);
			}
			else {
				SouthScore = SouthPae.CalcScore();
				NorthScore = NorthPae.CalcScore();
				if (SouthScore < 7 && NorthScore < 7) {
					OutPrompt("���� ��� �⺻ ������ ���� ���� �����ϴ�.");
					return;
				}
				SouthWin = (SouthScore > NorthScore);
			}
		}
		else {
			SouthWin = SouthTurn;
		}
		sprintf(Mes, "%s���� �̰���ϴ�. ", SouthWin ? "��" : "��");

		if (SouthWin) {
			TurnPae = &SouthPae;
			OtherPae = &NorthPae;
		}
		else {
			TurnPae = &NorthPae;
			OtherPae = &SouthPae;
		}
		for (i = 0; i < TurnPae->GetNum(); i++) {
			if (TurnPae->GetCard(i).GetKind() >= 3) TurnPee++;
			if (TurnPae->GetCard(i).GetKind() == 0) TurnLight++;
		}
		for (i = 0; i < OtherPae->GetNum(); i++) {
			if (OtherPae->GetCard(i).GetKind() >= 3) OtherPee++;
			if (OtherPae->GetCard(i).GetKind() == 0) OtherLight++;
		}

		if (TurnPee >= 10 && OtherPee < 5 && OtherPee != 0) {
			strcat(Mes, "������ �ǹ��Դϴ�. ");
		}
		if (TurnLight >= 3 && OtherLight == 0) {
			strcat(Mes, "������ �����Դϴ�. ");
		}
		if (OtherPae->GetGo() != 0) {
			strcat(Mes, "������ �����Դϴ�. ");
		}
		OutPrompt(Mes);
		gotoxy(40, 22);
		if (Blanket.GetNum() != 0) {
			printf("%d �������� �̻��� ����", k);
			getch();
		}
		else {
			printf("%d�� �׽�Ʈ �Ϸ�", k);
			delay(500);
		}
		SouthPae.Reset();
		NorthPae.Reset();
	}
}

void Initialize()
{
	int i;

	for (;;) {
		Deck.Reset();
		South.Reset();
		North.Reset();
		Blanket.Reset();
		Deck.Shuffle();
		for (i = 0; i < 10; i++) {
			South.InsertCard(Deck.Pop());
			North.InsertCard(Deck.Pop());
			if (i < 8) Blanket.InsertCard(Deck.Pop());
		}
		if (South.GetMaxSeries() != 4 && North.GetMaxSeries() != 4 && Blanket.GetMaxSeries() != 4)
			break;
	}
}

void DrawScreen()
{
	clrscr();
	South.Draw(SouthTurn);
	North.Draw(!SouthTurn);
	Blanket.Draw();
	Deck.Draw(false);
	SouthPae.Draw();
	NorthPae.Draw();
}

void OutPrompt(const char* Mes, int Wait/*=0*/)
{
	gotoxy(5, 23);
	for (int i = 5; i < 79; i++) { cout << ' '; }
	gotoxy(5, 23);
	cout << Mes;
	delay(Wait);
}

int InputInt(const char* Mes, int start, int end)
{
	return 1;
	int ch;

	OutPrompt(Mes);
	for (;;) {
		ch = tolower(getch());
		if (ch == 0xE0 || ch == 0) {
			ch = getch();
			continue;
		}
		if (!(isdigit(ch) || ch == 'a')) continue;
		if (ch == 'a') ch = 10; else ch = ch - '0';
		if (ch >= start && ch <= end) {
			return ch;
		}
		OutPrompt("��ȿ�� ��ȣ�Դϴ�. ������ ������ �°� �ٽ� �Է��� �ּ���.");
	}
}