#include <iostream>
#include <cassert>
#include <cstdlib>
#include <ctime>
#include <sstream>
using namespace std;

enum PetType {W, L, G};
enum PetSkill {Tackle, Leaf, Flame, Stream};

class Pet {
public:
    Pet(PetType p)
        :upet(p)
    { }

    PetType getType() const
    {
        return upet;
    }

    PetSkill getSkill() const
    {
        switch(upet) {
        case W:
            return Leaf;
        case L:
            return Flame;
        case G:
           return Stream;
        default:
            assert(false);
        }
    }

    void petInfo()
    {
        switch(upet) {
        case W:
            HP = 110, atk = 10, def = 10;
            break;
        case L:
            HP = 100, atk = 11, def = 10;
            break;
        case G:
            HP = 100, atk = 10, def = 11;
            break;
        default:
            assert(false);
        }
    }

    int getHP() const
    {
        return HP;
    }

    int getAtk() const
    {
        return atk;
    }

    int getDef() const
    {
        return def;
    }

    void atked(int damage)
    {
        HP -= damage;
    }

    bool petAlive() const
    {
        if(HP > 0)
            return true;
        else
            return false;
    }

    void getRevp()
    {
        switch(upet) {
        case W:
            HP = 55, atk = 10, def = 10;
            break;
        case L:
            HP = 50, atk = 11, def = 10;
            break;
        case G:
            HP = 50, atk = 10, def = 11;
            break;
        default:
            assert(false);
        }
    }

    void getAtkp()
    {
        atk *= 2;
    }

private:
    PetType upet;
    int HP, atk, def;
};

Pet p1(W), p2(L), p3(G);
Pet e1(W), e2(L), e3(G);
Pet nowp = p1, nowe = e1;
int n1 = 1, n2 = 2;
//get the different skill's different damage
int Damage(Pet p, Pet e, int n)
{
    PetType pt = p.getType();
    PetType et = e.getType();
    int def = e.getDef();
    if(n == 1)
        return 20 * p.getAtk() / def;
    else{
        switch(et) {
        case W:
            if(pt == L)
                return 20 * p.getAtk() / def * 2;
            else
                return 20 * p.getAtk() / def * 0.5;
        case L:
            if(pt == G)
                return 20 * p.getAtk() / def * 2;
            else
                return 20 * p.getAtk() / def * 0.5;
        case G:
            if(pt == W)
                return 20 * p.getAtk() / def * 2;
            else
                return 20 * p.getAtk() / def * 0.5;
        default:
            assert(false);
        }
    }
}

bool is_alive(Pet m, Pet n)
{
    return (m.petAlive() || n.petAlive());
}
//judge if m counter n
bool is_up(Pet m, Pet n)
{
    PetType m1 = m.getType(), n1 = n.getType();
    return (m1 == W && n1 == G) || (m1 == L && n1 == W) || (m1 == G && n1 == L);
}
//judge if pet gets a attack potion
bool is_normal(Pet p)
{
    switch(p.getType()) {
    case W:
        return (e1.getAtk() == 10);
    case L:
        return (e2.getAtk() == 11);
    case G:
        return (e3.getAtk() == 10);
    default:
        assert(false);
    }
}
//choose the start pet
PetType startPet(istream& is, ostream& os)
{
    os<<"Select your starting pet(1 for W,2 for L,3 for G): ";
    int n;
    is >> n;
    switch(n) {
    case 1:
        os<<"You start with W"<<endl;
        return W;
    case 2:
        os<<"You start with L"<<endl;
        return L;
    case 3:
        os<<"You start with G"<<endl;
        return G;
    default:
        return startPet(is, os);
    }
}
//cause your HP of pet decrease
void u_HPdamage(int n)
{
    switch(nowp.getType()) {
    case W:
        p1.atked(n);
        break;
    case L:
        p2.atked(n);
        break;
    case G:
        p3.atked(n);
        break;
    default:
        assert(false);
    }
}
//cause enemy's HP of pet decrease
void e_HPdamage(int n)
{
    switch(nowe.getType()) {
    case W:
        e1.atked(n);
        break;
    case L:
        e2.atked(n);
        break;
    case G:
        e3.atked(n);
        break;
    default:
        assert(false);
    }
}
//get Attack Potion
void getAttack(PetType p)
{
    switch(p) {
    case W:
        e1.getAtkp();
        break;
    case L:
        e2.getAtkp();
        break;
    case G:
        e3.getAtkp();
        break;
    default:
        assert(false);
    }
    n2--;
}
//get a potion
bool getPotion(bool &f1, bool &f2, int &n)
{
    if(!(e1.petAlive() && e2.petAlive() && e3.petAlive()) && (n1 > 0)){
        if(!e1.petAlive())
            e1.getRevp();
        if(!e2.petAlive()){
            e2.getRevp();
            n = 2;
        }
        if(!e3.petAlive()){
            e3.getRevp();
            n = 3;
        }
        n1--;
        f1 = true;
        return true;
    }else if(!is_up(nowp, nowe) && (n2 > 0)){
        if(is_normal(nowe)){
            getAttack(nowe.getType());
            nowe.getAtkp();
            f2 = true;
            switch(nowe.getType()){
            case W:
                n = 1;
                break;
            case L:
                n = 2;
                break;
            case G:
                n = 3;
                break;
            default:
                assert(false);
            }
            return true;
        }
        return false;
    }
        return false;
}
//show potion information
void showPotion(bool f1, bool f2, int p, ostream& os)
{
    if(f1){
        switch(p) {
        case 1:
            os<<"Enemy uses Revival Potion on W"<<endl;
            break;
        case 2:
            os<<"Enemy uses Revival Potion on L"<<endl;
            break;
        case 3:
            os<<"Enemy uses Revival Potion on G"<<endl;
            break;
        default:
            assert(false);
        }
    }
    if(f2){
        switch(p) {
        case 1:
            os<<"Enemy uses Attack Potion on W"<<endl;
            break;
        case 2:
            os<<"Enemy uses Attack Potion on L"<<endl;
            break;
        case 3:
            os<<"Enemy uses Attack Potion on G"<<endl;
            break;
        default:
            assert(false);
        }
    }
}
//enemy's attack
void enemyAtk(istream& is, ostream& os)
{
    if(!nowe.petAlive())
        return;

    if(is_up(nowe, nowp)){
        switch(nowe.getType()) {
        case W:
            os<<"Enemy's W uses Leaf! Damage: ";
            break;
        case L:
            os<<"Enemy's L uses Flame! Damage: ";
            break;
        case G:
            os<<"Enemy's G uses Stream! Damage: ";
            break;
        default:
            assert(false);
        }
        os<<Damage(nowe, nowp, 2)<<endl;
        u_HPdamage(Damage(nowe, nowp, 2));
        nowp.atked(Damage(nowe, nowp, 2));
    }else{
        switch(nowe.getType()) {
        case W:
            os<<"Enemy's W uses Tackle! Damage: ";
            break;
        case L:
            os<<"Enemy's L uses Tackle! Damage: ";
            break;
        case G:
            os<<"Enemy's G uses Tackle! Damage: ";
            break;
        default:
            assert(false);
        }
        os<<Damage(nowe, nowp, 1)<<endl;
        u_HPdamage(Damage(nowe, nowp, 1));
        nowp.atked(Damage(nowe, nowp, 1));
    }
}
//choose next pet
void nextPet(istream& is, ostream& os)
{
    bool flag1 = false, flag2 = false;
    int p = 1;
    PetType et = nowe.getType();
    if(!getPotion(flag1, flag2, p) && is_normal(nowe)){
        switch(nowp.getType()) {
        case W:
            if(e2.petAlive())
                nowe = e2;
            else if(e1.petAlive())
                nowe = e1;
            else
                nowe = e3;
            break;
        case L:
            if(e3.petAlive())
                nowe = e3;
            else if(e2.petAlive())
                nowe = e2;
            else
                nowe = e1;
            break;
        case G:
            if(e1.petAlive())
                nowe = e1;
            else if(e3.petAlive())
                nowe = e3;
            else
                nowe = e2;
            break;
        default:
            assert(false);
        }
    }
    PetType pt = nowp.getType();
    os<<"Select your next pet ";
    switch(pt) {
    case W:
        if(p2.petAlive() && p3.petAlive())
            os<<"(2 for L,3 for G): ";
        else if(p2.petAlive())
            os<<"(2 for L): ";
        else
            os<<"(3 for G): ";
        break;
    case L:
        if(p1.petAlive() && p3.petAlive())
            os<<"(1 for W,3 for G): ";
        else if(p2.petAlive())
            os<<"(1 for W): ";
        else
            os<<"(3 for G): ";
        break;
    case G:
        if(p2.petAlive() && p1.petAlive())
            os<<"(1 for W,2 for L): ";
        else if(p2.petAlive())
            os<<"(2 for L): ";
        else
            os<<"(1 for W): ";
        break;
    default:
        assert(false);
    }
    int n;
    is >> n;
    if(et != nowe.getType()){
        switch(nowe.getType()) {
        case W:
            os<<"Enemy sends W"<<endl;
            break;
        case L:
            os<<"Enemy sends L"<<endl;
            break;
        case G:
            os<<"Enemy sends G"<<endl;
            break;
        default:
            assert(false);
        }
    }
    bool flag = (flag1 || flag2);
    if(n == 1 && p1.petAlive()){
        os<<"You send W"<<endl;
        nowp = p1;
        if(!flag && (et == nowe.getType()))
            enemyAtk(is, os);
        else
            showPotion(flag1, flag2, p, os);
    }else if(n == 2 && p2.petAlive()){
        os<<"You send L"<<endl;
        nowp = p2;
        if(!flag && (et == nowe.getType()))
            enemyAtk(is, os);
        showPotion(flag1, flag2, p, os);
    }else if(n == 3 && p3.petAlive()){
        os<<"You send G"<<endl;
        nowp = p3;
        if(!flag && (et == nowe.getType()))
            enemyAtk(is, os);
        else
            showPotion(flag1, flag2, p, os);
    }else
        nextPet(is, os);
}
//after a pet die
void changePet(istream& is, ostream& os)
{
    PetType pt = nowp.getType();
    os<<"Select your next pet ";
    switch(pt) {
    case W:
        if(p2.petAlive() && p3.petAlive())
            os<<"(2 for L,3 for G): ";
        else if(p2.petAlive())
            os<<"(2 for L): ";
        else
            os<<"(3 for G): ";
        break;
    case L:
        if(p1.petAlive() && p3.petAlive())
            os<<"(1 for W,3 for G): ";
        else if(p2.petAlive())
            os<<"(1 for W): ";
        else
            os<<"(3 for G): ";
        break;
    case G:
        if(p2.petAlive() && p1.petAlive())
            os<<"(1 for W,2 for L): ";
        else if(p2.petAlive())
            os<<"(2 for L): ";
        else
            os<<"(1 for W): ";
        break;
    default:
        assert(false);
    }
    int n;
    is >> n;
    if(n == 1 && p1.petAlive()){
        os<<"You send W"<<endl;
        nowp = p1;
    }else if(n == 2 && p2.petAlive()){
        os<<"You send L"<<endl;
        nowp = p2;
    }else if(n == 3 && p3.petAlive()){
        os<<"You send G"<<endl;
        nowp = p3;
    }else
        changePet(is, os);
}
//enemy's next pet
PetType enemy_nextpet()
{
    if(nowp.petAlive()){
        switch(nowp.getType()) {
        case W:
            if(e2.petAlive())
                return L;
            else if(e1.petAlive())
                return W;
            else
                return G;
        case L:
            if(e3.petAlive())
                return G;
            else if(e2.petAlive())
                return L;
            else
                return W;
        case G:
            if(e1.petAlive())
                return W;
            else if(e3.petAlive())
                return G;
            else
                return L;
        default:
            assert(false);
        }
    }else{
        switch(nowp.getType()) {
        case W:
            if(e3.petAlive())
                return G;
            else if(e1.petAlive())
                return W;
            else
                return L;
        case L:
            if(e1.petAlive())
                return W;
            else if(e2.petAlive())
                return L;
            else
                return G;
        case G:
            if(e2.petAlive())
                return L;
            else if(e3.petAlive())
                return G;
            else
                return W;
        default:
            assert(false);
        }
    }
}
//use a skill
void selectSki(istream& is, ostream& os)
{
    bool flag1 = false, flag2 = false;
    int p = 1;
    PetType et = nowe.getType();
    if(!getPotion(flag1, flag2, p) && is_normal(nowe)){
        switch(nowp.getType()) {
        case W:
            if(e2.petAlive())
                nowe = e2;
            else if(e1.petAlive())
                nowe = e1;
            else
                nowe = e3;
            break;
        case L:
            if(e3.petAlive())
                nowe = e3;
            else if(e2.petAlive())
                nowe = e2;
            else
                nowe = e1;
            break;
        case G:
            if(e1.petAlive())
                nowe = e1;
            else if(e3.petAlive())
                nowe = e3;
            else
                nowe = e2;
            break;
        default:
            assert(false);
        }
    }
    PetSkill pski = nowp.getSkill();
    switch(pski) {
    case Leaf:
        os<<"Select the skill (1 for Tackle,2 for Leaf): ";
        break;
    case Flame:
        os<<"Select the skill (1 for Tackle,2 for Flame): ";
        break;
    case Stream:
        os<<"Select the skill (1 for Tackle,2 for Stream): ";
        break;
    default:
        assert(false);
    }
    int n;
    is >> n;

    if(et != nowe.getType()){
        switch(nowe.getType()) {
        case W:
            os<<"Enemy sends W"<<endl;
            break;
        case L:
            os<<"Enemy sends L"<<endl;
            break;
        case G:
            os<<"Enemy sends G"<<endl;
            break;
        default:
            assert(false);
        }
    }
    showPotion(flag1, flag2, p, os);
    if(n == 1){
        switch(nowp.getType()) {
        case W:
            os<<"Your W uses Tackle! Damage: ";
            break;
        case L:
            os<<"Your L uses Tackle! Damage: ";
            break;
        case G:
            os<<"Your G uses Tackle! Damage: ";
            break;
        default:
            assert(false);
        }
        os<<Damage(nowp, nowe, 1)<<endl;
        if(et == nowe.getType() && !flag1 && !flag2)
            enemyAtk(is, os);
        e_HPdamage(Damage(nowp, nowe, 1));
        nowe.atked(Damage(nowp, nowe, 1));
    }else if(n == 2){
        switch(nowp.getType()) {
        case W:
            os<<"Your W uses Leaf! Damage: ";
            break;
        case L:
            os<<"Your L uses Flame! Damage: ";
            break;
        case G:
            os<<"Your G uses Stream! Damage: ";
            break;
        default:
            assert(false);
        }
        os<<Damage(nowp, nowe, 2)<<endl;
        if(et == nowe.getType() && !flag1 && !flag2)
            enemyAtk(is, os);
        e_HPdamage(Damage(nowp, nowe, 2));
        nowe.atked(Damage(nowp, nowe, 2));
    }else
        selectSki(is, os);
}
//player choose a action
void selectAct(istream& is, ostream& os)
{
    bool flag = false;
    if(!is_alive(p1, p2) && nowp.getType() == p3.getType())
        os<<"Select your action (1 for skill): ";
    else if(!is_alive(p1, p3) && nowp.getType() == p2.getType())
        os<<"Select your action (1 for skill): ";
    else if(!is_alive(p2, p3) && nowp.getType() == p1.getType())
        os<<"Select your action (1 for skill): ";
    else{
        os<<"Select your action (0 for change,1 for skill): ";
        flag = true;
    }
    int n;
    is >> n;
    if(n == 1)
        selectSki(is, os);
    else if(n == 0 && flag){
        nextPet(is, os);
    }else
        selectAct(is, os);
}

void showHP(ostream& os)
{
    switch(nowp.getType()) {
    case W:
        os<<"Your W: HP "<<p1.getHP();
        break;
    case L:
        os<<"Your L: HP "<<p2.getHP();
        break;
    case G:
        os<<"Your G: HP "<<p3.getHP();
        break;
    default:
        assert(false);
    }
    os<<" || ";
    switch(nowe.getType()) {
    case W:
        os<<"Enemy's W: HP "<<e1.getHP();
        break;
    case L:
        os<<"Enemy's L: HP "<<e2.getHP();
        break;
    case G:
        os<<"Enemy's G: HP "<<e3.getHP();
        break;
    default:
        assert(false);
    }
    os<<endl;
}

void play(istream& is, ostream& os)
{
    //Before battle
    os<<"Welcome to Battle of Pets!"<<endl;
    os<<"You have W,L and G.So does Enemy."<<endl;
    PetType stpet = startPet(is, os);
    srand(time(0));
    int enemy_start = rand() % 3 + 1;
    switch(enemy_start) {
    case 1:
        os<<"Enemy starts with W"<<endl;
        break;
    case 2:
        os<<"Enemy starts with L"<<endl;
        break;
    case 3:
        os<<"Enemy starts with G"<<endl;
        break;
    default:
        assert(false);
    }
    if(stpet == W)
        nowp = p1;
    else if(stpet == L)
        nowp = p2;
    else
        nowp = p3;

    if(enemy_start == 1)
        nowe = e1;
    else if(enemy_start == 2)
        nowe = e2;
    else
        nowe = e3;

    showHP(os);
    os<<"Battle starts!"<<endl;
    //while in battle

    int rnum = 1;
    while(is)
    {
        for(int i = 1;i <= 50;i++)
            os<<"-";
        os<<endl;
        os<<"Round "<<rnum<<endl;

        selectAct(is, os);
        PetType et = nowe.getType();
        if(!nowe.petAlive()){
            switch(et) {
            case W:
                os<<"Enemy's W is beaten"<<endl;
                break;
            case L:
                os<<"Enemy's L is beaten"<<endl;
                break;
            case G:
                os<<"Enemy's G is beaten"<<endl;
                break;
            default:
                assert(false);
            }
            if(!e1.petAlive() && !e2.petAlive() && !e3.petAlive()){
                if(!nowp.petAlive()){
                    switch(nowp.getType()) {
                    case W:
                        os<<"Your W is beaten"<<endl;
                        break;
                    case L:
                        os<<"Your L is beaten"<<endl;
                        break;
                    case G:
                        os<<"Your G is beaten"<<endl;
                        break;
                    default:
                        assert(false);
                    }
                    if(p1.petAlive() || p2.petAlive() || p3.petAlive())
                        changePet(is, os);
                }
                if(p1.petAlive() || p2.petAlive() || p3.petAlive())
                    os<<"You Win"<<endl;
                else
                    os<<"Draw"<<endl;
                break;
            }
            et = enemy_nextpet();
        }

        if(!nowp.petAlive()){
            switch(nowp.getType()) {
            case W:
                os<<"Your W is beaten"<<endl;
                break;
            case L:
                os<<"Your L is beaten"<<endl;
                break;
            case G:
                os<<"Your G is beaten"<<endl;
                break;
            default:
                assert(false);
            }
            if(!p1.petAlive() && !p2.petAlive() && !p3.petAlive()){
                if(et != nowe.getType()){
                    switch(et) {
                    case W:
                        os<<"Enemy sends W"<<endl;
                        break;
                    case L:
                        os<<"Enemy sends L"<<endl;
                        break;
                    case G:
                        os<<"Enemy sends G"<<endl;
                        break;
                    default:
                        assert(false);
                    }
                }
                if(e1.petAlive() || e2.petAlive() || e3.petAlive())
                    os<<"You Lose"<<endl;
                else
                    os<<"Draw"<<endl;
                break;
            }
            changePet(is, os);
        }
        if(et != nowe.getType()){
            switch(et) {
            case W:
                os<<"Enemy sends W"<<endl;
                nowe = e1;
                break;
            case L:
                os<<"Enemy sends L"<<endl;
                nowe = e2;
                break;
            case G:
                os<<"Enemy sends G"<<endl;
                nowe = e3;
                break;
            default:
                assert(false);
            }
        }
        showHP(os);
        rnum++;
        if(rnum > 100){
            os<<"Draw"<<endl;
            break;
        }
    }
}

int main()
{
    p1.petInfo(), p2.petInfo(), p3.petInfo();
    e1.petInfo(), e2.petInfo(), e3.petInfo();
    play(cin, cout);
    return 0;
}
