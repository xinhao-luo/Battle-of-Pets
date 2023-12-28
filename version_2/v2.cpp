#include <iostream>
#include <cassert>
#include <vector>
#include <ctime>
using namespace std;

enum PetType {W, L, G, Q, D, N};
class Pet {
public:
    Pet()
        :upet(N)
    { }

    Pet(PetType p)
        :upet(p)
    { }

    PetType getType() const
    {
        return upet;
    }

    void petInfo()
    {
        switch(upet) {
        case W:
            HP = 110, atk = 10, def = 10, spd = 10;
            break;
        case L:
            HP = 100, atk = 12, def = 10, spd = 11;
            break;
        case G:
            HP = 100, atk = 10, def = 14, spd = 9;
            break;
        case Q:
            HP = 90, atk = 10, def = 10, spd = 12;
            break;
        case D:
            HP = 120, atk = 9, def = 8, spd = 7;
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

    int getSpd() const
    {
        return spd;
    }

    string strType() const
    {
        switch(upet) {
        case W:
            return "W";
        case L:
            return "L";
        case G:
            return "G";
        case Q:
            return "Q";
        case D:
            return "D";
        default:
            assert(false);
        }
    }

    void atked(int n)
    {
        HP -= n;
    }

    int maxHP() const
    {
        switch(upet) {
        case W:
            return 110;
        case L:
            return 100;
        case G:
            return 100;
        case Q:
            return 90;
        case D:
            return 120;
        default:
            assert(false);
        }
    }

    void rec(int n)
    {
        HP += n;
        if(HP > maxHP())
            HP = maxHP();
    }

    bool petAlive() const
    {
        if(HP > 0)
            return true;
        else
            return false;
    }

    void fallAsleep()
    {
        asleep = true;
    }

    void awake()
    {
        asleep = false;
    }

    void bePainted()
    {
        bept = true;
        switch(upet) {
        case W:
            def = 5;
            break;
        case L:
            def = 5;
            break;
        case G:
            def = 7;
            break;
        case Q:
            def = 5;
            break;
        case D:
            def = 4;
            break;
        default:
            assert(false);
        }
    }

    bool petAsleep() const
    {
        return asleep;
    }

    bool petPaint() const
    {
        return bept;
    }

    void getRevp()
    {
        switch(upet) {
        case W:
            HP = 55;
            break;
        case L:
            HP = 50;
            break;
        case G:
            HP = 50;
            break;
        case Q:
            HP = 45;
            break;
        case D:
            HP = 60;
            break;
        default:
            assert(false);
        }
    }
private:
    PetType upet;
    int HP, atk, def, spd;
    bool asleep = false, bept = false;
};

Pet p1(W), p2(L), p3(G), p4(Q), p5(D);
Pet e1(W), e2(G), e3(Q);
vector<Pet> team = {p1, p2, p3, p4, p5};
vector<Pet> pteam;
Pet np1, np2, np3;
Pet nowp, nowe;
bool engine = true;
int w = 1;
int anum1 = 0, anum2 = 0, anum3 = 0;
int bnum1 = 0, bnum2 = 0, bnum3 = 0;
int rnum = 1, wnum = 0;
int pski = 1, eski = 1, rev = 1, pd = 0, ed = 0, pd1 = 0, ed1 = 0;
//choose player's team
void pTeam(istream& is, ostream& os)
{
    os<<"You can select three from five(1 for W,2 for L,3 for G,4 for Q,5 for D)."<<endl;
    int n = 1;
    while(n <= 3){
        os<<"Select your ";
        if(n == 1)
            os<<"1st ";
        else if(n == 2)
            os<<"2nd ";
        else
            os<<"3rd ";
        os<<"pet: ";
        int p;
        is >> p;
        bool flag = true;
        if(p < 0 || p > 5)
            continue;
        else{
            int l = pteam.size();
            for(int i = 0;i < l;i++){
                if(pteam[i].getType() == team[p - 1].getType()){
                    flag = false;
                    break;
                }
            }
            if(!flag)
                continue;
            else{
                pteam.push_back(team[p - 1]);
                if(n == 1)
                    np1 = team[p - 1];
                else if(n == 2)
                    np2 = team[p - 1];
                else
                    np3 = team[p - 1];
                n++;
            }
        }
    }
    np1.petInfo(), np2.petInfo(), np3.petInfo();
    os<<"You have "<<np1.strType()<<","<<np2.strType()<<" and "<<np3.strType()<<"."<<endl;
    os<<"You start with "<<np1.strType()<<endl;
}
//get the different skill's different damage
int Damage(Pet p, Pet e, int n)
{
    PetType pt = p.getType();
    PetType et = e.getType();
    int def = e.getDef();
    if(n == 1){
        switch(pt) {
        case W:
            return int(20.0 * p.getAtk() / def + 0.5);
        case L:
            return int(15.0 * p.getAtk() / def + 0.5);
        case G:
            return int(20.0 * p.getAtk() / def + 0.5);
        case Q:
            return int(15.0 * p.getAtk() / def + 0.5);
        case D:
            if(e.petAsleep())
                return int(30.0 * p.getAtk() / def + 0.5);
            else
                return int(15.0 * p.getAtk() / def + 0.5);
        default:
            assert(false);
        }
    }else if(n == 2){
        switch(et) {
        case W:
            if(pt == L){
                if(w == 2)
                    return int(30.0 * p.getAtk() / def * 2 + 0.5);
                else if(w == 3)
                    return int(10.0 * p.getAtk() / def * 2 + 0.5);
                else
                    return int(20.0 * p.getAtk() / def * 2 + 0.5);
            }else if(pt == G){
                if(w == 2)
                    return int(10.0 * p.getAtk() / def * 0.5 + 0.5);
                else if(w == 3)
                    return int(30.0 * p.getAtk() / def * 0.5 + 0.5);
                else
                    return int(20.0 * p.getAtk() / def * 0.5 + 0.5);
            }else if(pt == W)
                return int(20.0 * p.getAtk() / def * 0.5 + 0.5);
            else
                return int(25.0 * p.getAtk() / def * 0.5 + 0.5);
        case L:
            if(pt == G){
                if(w == 2)
                    return int(10.0 * p.getAtk() / def * 2 + 0.5);
                else if(w == 3)
                    return int(30.0 * p.getAtk() / def * 2+ 0.5);
                else
                    return int(20.0 * p.getAtk() / def * 2 + 0.5);
            }else if(pt == L){
                if(w == 2)
                    return int(30.0 * p.getAtk() / def * 0.5 + 0.5);
                else if(w == 3)
                    return int(10.0 * p.getAtk() / def * 0.5 + 0.5);
                else
                    return int(20.0 * p.getAtk() / def * 0.5 + 0.5);
            }else if(pt == W)
                return int(20.0 * p.getAtk() / def * 0.5 + 0.5);
            else
                return int(25.0 * p.getAtk() / def + 0.5);
        case G:
            if(pt == W)
                return int(20.0 * p.getAtk() / def * 2 +0.5);
            else if(pt == L){
                if(w == 2)
                    return int(30.0 * p.getAtk() / def * 0.5 + 0.5);
                else if(w == 3)
                    return int(10.0 * p.getAtk() / def * 0.5 + 0.5);
                else
                    return int(20.0 * p.getAtk() / def * 0.5 + 0.5);
            }else if(pt == G){
                if(w == 2)
                    return int(10.0 * p.getAtk() / def * 0.5 + 0.5);
                else if(w == 3)
                    return int(30.0 * p.getAtk() / def * 0.5 + 0.5);
                else
                    return int(20.0 * p.getAtk() / def * 0.5 + 0.5);
            }else
                return int(25.0 * p.getAtk() / def * 2 + 0.5);
        case Q:
            if(pt == W)
                return int(20.0 * p.getAtk() / def +0.5);
            else if(pt == L){
                if(w == 2)
                    return int(30.0 * p.getAtk() / def + 0.5);
                else if(w == 3)
                    return int(10.0 * p.getAtk() / def + 0.5);
                else
                    return int(20.0 * p.getAtk() / def + 0.5);
            }else if(pt == G){
                if(w == 2)
                    return int(10.0 * p.getAtk() / def + 0.5);
                else if(w == 3)
                    return int(30.0 * p.getAtk() / def + 0.5);
                else
                    return int(20.0 * p.getAtk() / def + 0.5);
            }else
                return int(25.0 * p.getAtk() / def * 0.5 + 0.5);
        case D:
            if(pt == W)
                return int(20.0 * p.getAtk() / def +0.5);
            else if(pt == L){
                if(w == 2)
                    return int(30.0 * p.getAtk() / def + 0.5);
                else if(w == 3)
                    return int(10.0 * p.getAtk() / def + 0.5);
                else
                    return int(20.0 * p.getAtk() / def + 0.5);
            }else if(pt == G){
                if(w == 2)
                    return int(10.0 * p.getAtk() / def + 0.5);
                else if(w == 3)
                    return int(30.0 * p.getAtk() / def + 0.5);
                else
                    return int(20.0 * p.getAtk() / def + 0.5);
            }else
                return int(25.0 * p.getAtk() / def + 0.5);
        default:
            assert(false);
        }
    }else{
        switch(et){
        case W:
            return int(50.0 * p.getAtk() / def * 0.5 + 0.5);
        case L:
            return int(50.0 * p.getAtk() / def + 0.5);
        case G:
            return int(50.0 * p.getAtk() / def * 2 + 0.5);
        case Q:
            return int(50.0 * p.getAtk() / def * 0.5 + 0.5);
        case D:
            return int(50.0 * p.getAtk() / def + 0.5);
        }
    }
}
//get the recovery HP
int Recovery()
{
    if(w == 2)
        return 44;
    else if(w == 3)
        return 22;
    else
        return 33;
}
bool is_alive(Pet m, Pet n)
{
    return (m.petAlive() || n.petAlive());
}
//cause your HP of pet decrease
void u_HPdamage(int n)
{
    PetType pt = nowp.getType();
    if(pt == np1.getType()){
        np1.atked(n);
        np1.awake();
    }
    else if(pt == np2.getType()){
        np2.atked(n);
        np2.awake();
    }
    else{
        np3.atked(n);
        np3.awake();
    }
    nowp.atked(n);
}
//cause enemy's HP of pet decrease
void e_HPdamage(int n)
{
    switch(nowe.getType()) {
    case W:
        e1.atked(n);
        e1.awake();
        break;
    case G:
        e2.atked(n);
        e2.awake();
        break;
    case Q:
        e3.atked(n);
        e3.awake();
        break;
    default:
        assert(false);
    }
    nowe.atked(n);
}
//enemy's attack
void enemyAtk(ostream& os, Pet p)
{
    if(!nowe.petAlive())
        return;
    if(pd != 0){
        if(nowe.getHP() <= pd1)
            return;
    }
    if(nowe.petAsleep()){
        os<<"Enemy's "<<nowe.strType()<<" is sleeping"<<endl;
        return;
    }
    if(!e2.petAlive() && rev > 0){
        os<<"Enemy uses Revival Potion on G"<<endl;
        e2.getRevp();
        rev--;
        return;
    }
    if(nowe.getType() == W){
        if(p.getType() == L){
            if(e2.petAlive()){
                os<<"Enemy sends G"<<endl;
                nowe = e2;
            }else{
                if(nowe.getHP() >= 73){
                    os<<"Enemy's W uses Tackle! Damage: "<<Damage(nowe, nowp, 1)<<endl;
                    ed = 1;
                    ed1 = Damage(nowe, nowp, 1);
                }else{
                    os<<"Enemy's W uses Synthesis! Recovery: "<<Recovery()<<endl;
                    e1.rec(Recovery());
                    nowe.rec(Recovery());
                }
                eski = 2;
            }
        }else if(p.getType() == W){
            if(nowe.getHP() >= 55){
                os<<"Enemy's W uses Tackle! Damage: "<<Damage(nowe, nowp, 1)<<endl;
                ed = 1;
                ed1 = Damage(nowe, nowp, 1);
            }else{
                os<<"Enemy's W uses Synthesis! Recovery: "<<Recovery()<<endl;
                e1.rec(Recovery());
                nowe.rec(Recovery());
            }
            eski = 2;
        }else{
            if(nowe.getHP() >= 55 || nowp.getHP() < int(p.maxHP() * 1.0 / 5 +0.5)){
                os<<"Enemy's W uses Leaf! Damage: "<<Damage(nowe, nowp, 2)<<endl;
                ed = 2;
                ed1 = Damage(nowe, nowp, 2);
            }else{
                os<<"Enemy's W uses Synthesis! Recovery: "<<Recovery()<<endl;
                e1.rec(Recovery());
                nowe.rec(Recovery());
            }
            eski = 2;
        }
    }else if(nowe.getType() == G){
        if(w == 2){
            os<<"Enemy's G uses Rainy! Weather becomes rainy"<<endl;
            w = 3;
            wnum = 0;
            eski = 2;
        }else{
            if(p.getType() == Q || (p.getType() == W && w == 3)){
                if(e1.petAlive()){
                    os<<"Enemy sends W"<<endl;
                    nowe = e1;
                }else{
                    if(w == 2 && e3.petAlive()){
                        os<<"Enemy sends Q"<<endl;
                        nowe = e3;
                    }else{
                        os<<"Enemy's G uses Stream! Damage: "<<Damage(nowe, nowp, 2)<<endl;
                        ed = 2;
                        ed1 = Damage(nowe, nowp, 2);
                        eski = 2;
                    }
                }
            }else if(p.getType() == G){
                os<<"Enemy's G uses Tackle! Damage: "<<Damage(nowe, nowp, 1)<<endl;
                ed = 1;
                ed1 = Damage(nowe, nowp, 1);
                eski = 2;
            }else{
                if(w == 3){
                    os<<"Enemy's G uses Stream! Damage: "<<Damage(nowe, nowp, 2)<<endl;
                    ed = 2;
                    ed1 = Damage(nowe, nowp, 2);
                }else{
                    os<<"Enemy's G uses Rainy! Weather becomes rainy"<<endl;
                    w = 3;
                    wnum = 0;
                }
                eski = 2;
            }
        }
    }else{
        if(p.getHP() < int(p.maxHP() * 1.0 / 5 +0.5)){
            os<<"Enemy's Q uses Quick! Damage: "<<Damage(nowe, nowp, 1)<<endl;
            ed = 1;
            ed1 = Damage(nowe, nowp, 1);
            eski = 2;
        }else{
            if(p.getType() == L){
                if(e2.petAlive()){
                    os<<"Enemy sends G"<<endl;
                    nowe = e2;
                }else{
                    os<<"Enemy's Q uses Volt! Damage: "<<Damage(nowe, nowp, 2)<<endl;
                    ed = 2;
                    ed1 = Damage(nowe, nowp, 2);
                    eski = 2;
                }
            }else{
                if(w == 3){
                    os<<"Enemy's Q uses Thunder! Damage: "<<Damage(nowe, nowp, 3)<<endl;
                    ed = 3;
                    ed1 = Damage(nowe, nowp, 3);
                    eski = 2;
                }else{
                    if(e1.petAlive()){
                        os<<"Enemy sends W"<<endl;
                        nowe = e1;
                    }else{
                        if(p.getType() == Q || p.getType() == W){
                            os<<"Enemy's Q uses Quick! Damage: "<<Damage(nowe, nowp, 1)<<endl;
                            ed = 1;
                            ed1 = Damage(nowe, nowp, 1);
                        }else{
                            os<<"Enemy's Q uses Volt! Damage: "<<Damage(nowe, nowp, 2)<<endl;
                            ed = 2;
                            ed1 = Damage(nowe, nowp, 2);
                        }
                        eski = 2;
                    }
                }
            }
        }
    }
    if(ed != 0){
        if(nowp.petAsleep()){
            nowp.awake();
            if(nowp.getType() == np1.getType())
                anum1 = 0;
            else if(nowp.getType() == np2.getType())
                anum2 = 0;
            else
                anum3 = 0;
            if(nowp.petAlive() && nowp.getHP() > ed1)
                os<<"Your "<<nowp.strType()<<" wakes up"<<endl;
        }
    }
}
//get the enemy's skill priority
int enemyPri()
{
    if(!e2.petAlive() && rev > 0)
        return 5;
    if(nowe.getType() == W){
        if(nowp.getType() == L){
            if(e2.petAlive())
                return 6;
            else{
                cout<<0<<endl;
                return 0;
            }
        }else
            return 0;
    }else if(nowe.getType() == G){
        if(w == 2)
            return 1;
        else{
            if(nowp.getType() == Q || (nowp.getType() == W && w == 3)){
                if(e1.petAlive())
                    return 6;
                else{
                    if(w == 2 && e3.petAlive())
                        return 6;
                    else
                        return 0;
                }
            }else if(nowp.getType() == G)
                return 0;
            else{
                if(w == 3)
                    return 0;
                else
                    return 1;
            }
        }
    }else{
        if(nowp.getHP() < int(nowp.maxHP() * 1.0 / 5 +0.5))
            return 1;
        else{
            if(nowp.getType() == L){
                if(e2.petAlive())
                    return 6;
                else
                    return 0;
            }else{
                if(w == 3)
                    return 0;
                else{
                    if(e1.petAlive())
                        return 6;
                    else{
                        if(nowp.getType() == Q || nowp.getType() == W)
                            return 1;
                        else
                            return 0;
                    }
                }
            }
        }
    }
}
//get player's skill priority
int playerPri(int n)
{
    switch(nowp.getType()){
    case W:
        return 0;
    case L:
        if(n == 3)
            return 1;
        else
            return 0;
    case G:
        if(n == 3)
            return 1;
        else
            return 0;
    case Q:
        if(n == 1)
            return 1;
        else
            return 0;
    case D:
        return 0;
    default:
        assert(false);
    }
}
//after a pet die
void changePet(istream& is, ostream& os)
{
    PetType pt = nowp.getType();
    os<<"Select your next pet ";
    if(pt == np1.getType()){
        if(np2.petAlive() && np3.petAlive())
            os<<"(2 for "<<np2.strType()<<"-HP"<<np2.getHP()<<", 3 for "<<np3.strType()<<"-HP"<<np3.getHP()<<"): ";
        else if(np2.petAlive())
            os<<"(2 for "<<np2.strType()<<"-HP"<<np2.getHP()<<"): ";
        else
            os<<"(3 for "<<np3.strType()<<"-HP"<<np3.getHP()<<"): ";
    }else if(pt == np2.getType()){
        if(np1.petAlive() && np3.petAlive())
            os<<"(1 for "<<np1.strType()<<"-HP"<<np1.getHP()<<", 3 for "<<np3.strType()<<"-HP"<<np3.getHP()<<"): ";
        else if(np1.petAlive())
            os<<"(1 for "<<np1.strType()<<"-HP"<<np1.getHP()<<"): ";
        else
            os<<"(3 for "<<np3.strType()<<"-HP"<<np3.getHP()<<"): ";
    }else{
        if(np1.petAlive() && np2.petAlive())
            os<<"(1 for "<<np1.strType()<<"-HP"<<np1.getHP()<<", 2 for "<<np2.strType()<<"-HP"<<np2.getHP()<<"): ";
        else if(np2.petAlive())
            os<<"(2 for "<<np2.strType()<<"-HP"<<np2.getHP()<<"): ";
        else
            os<<"(1 for "<<np1.strType()<<"-HP"<<np1.getHP()<<"): ";
    }
    int n;
    is >> n;
    if(n == 1 && np1.petAlive()){
        os<<"You send "<<np1.strType()<<endl;
        nowp = np1;
    }else if(n == 2 && np2.petAlive()){
        os<<"You send "<<np2.strType()<<endl;
        nowp = np2;
    }else if(n == 3 && np3.petAlive()){
        os<<"You send "<<np3.strType()<<endl;
        nowp = np3;
    }else
        changePet(is, os);
}
void selectAct(istream& is, ostream& os);
//choose next pet
void nextPet(istream& is, ostream& os)
{
    PetType pt = nowp.getType();
    PetType et = nowe.getType();
    os<<"Select your next pet ";
    if(pt == np1.getType()){
        if(np2.petAlive() && np3.petAlive())
            os<<"(0 for back, 2 for "<<np2.strType()<<"-HP"<<np2.getHP()<<", 3 for "<<np3.strType()<<"-HP"<<np3.getHP()<<"): ";
        else if(np2.petAlive())
            os<<"(0 for back, 2 for "<<np2.strType()<<"-HP"<<np2.getHP()<<"): ";
        else
            os<<"(0 for back, 3 for "<<np3.strType()<<"-HP"<<np3.getHP()<<"): ";
    }else if(pt == np2.getType()){
        if(np1.petAlive() && np3.petAlive())
            os<<"(0 for back, 1 for "<<np1.strType()<<"-HP"<<np1.getHP()<<", 3 for "<<np3.strType()<<"-HP"<<np3.getHP()<<"): ";
        else if(np1.petAlive())
            os<<"(0 for back, 1 for "<<np1.strType()<<"-HP"<<np1.getHP()<<"): ";
        else
            os<<"(0 for back, 3 for "<<np3.strType()<<"-HP"<<np3.getHP()<<"): ";
    }else{
        if(np1.petAlive() && np2.petAlive())
            os<<"(0 for back, 1 for "<<np1.strType()<<"-HP"<<np1.getHP()<<", 2 for "<<np2.strType()<<"-HP"<<np2.getHP()<<"): ";
        else if(np2.petAlive())
            os<<"(0 for back, 2 for "<<np2.strType()<<"-HP"<<np2.getHP()<<"): ";
        else
            os<<"(0 for back, 1 for "<<np1.strType()<<"-HP"<<np1.getHP()<<"): ";
    }
    int n;
    is >> n;
    if(enemyPri() >= 6)
        enemyAtk(os, nowp);
    if(n == 1 && np1.petAlive() && pt != np1.getType()){
        os<<"You send "<<np1.strType()<<endl;
        Pet p = nowp;
        nowp = np1;
        if(et == nowe.getType()){
            enemyAtk(os, p);
            u_HPdamage(ed1);
        }
    }else if(n == 2 && np2.petAlive() && pt != np2.getType()){
        os<<"You send "<<np2.strType()<<endl;
        Pet p = nowp;
        nowp = np2;
        if(et == nowe.getType()){
            enemyAtk(os, p);
            u_HPdamage(ed1);
        }
    }else if(n == 3 && np3.petAlive() && pt != np3.getType()){
        os<<"You send "<<np3.strType()<<endl;
        Pet p = nowp;
        nowp = np3;
        if(et == nowe.getType()){
            enemyAtk(os, p);
            u_HPdamage(ed1);
        }
    }else if(n == 0)
        selectAct(is, os);
    else
        nextPet(is, os);
}
//enemy's next pet
PetType enemy_nextpet()
{
    if(nowe.getType() == W){
        if(e2.petAlive())
            return G;
        else
            return Q;
    }else if(nowe.getType() == Q){
        if(e2.petAlive())
            return G;
        else
            return W;
    }else{
        if(e1.petAlive())
            return W;
        else
            return Q;
    }
}
void makeSki(ostream& os, int n);
//use a skill
void selectSki(istream& is, ostream& os)
{
    switch(nowp.getType()) {
    case W:
        os<<"Select the skill (0 for back, 1 for Tackle, 2 for Leaf, 3 for Synthesis): ";
        break;
    case L:
        os<<"Select the skill (0 for back, 1 for Claw, 2 for Flame, 3 for Sunny): ";
        break;
    case G:
        os<<"Select the skill (0 for back, 1 for Tackle, 2 for Stream, 3 for Rainy): ";
        break;
    case Q:
        os<<"Select the skill (0 for back, 1 for Quick, 2 for Volt, 3 for Thunder): ";
        break;
    case D:
        os<<"Select the skill (0 for back, 1 for Slap, 2 for Sing, 3 for Paint): ";
        break;
    default:
        assert(false);
    }
    int n;
    is >> n;
    if(n == 0)
        selectAct(is, os);
    else if(n < 0 || n > 3)
        selectSki(is, os);
    else{
        if(enemyPri() > playerPri(n)){
            enemyAtk(os, nowp);
            makeSki(os, n);
        }else if(enemyPri() < playerPri(n)){
            makeSki(os, n);
            enemyAtk(os, nowp);
        }else{
            if(nowp.getSpd() > nowe.getSpd()){
                makeSki(os, n);
                enemyAtk(os, nowp);
            }else{
                enemyAtk(os, nowp);
                makeSki(os, n);
            }
        }
        u_HPdamage(ed1);
        e_HPdamage(pd1);
    }
}
//player's pet do a skill
void makeSki(ostream& os, int n)
{
    if(!nowp.petAlive())
        return;
    if(ed != 0){
        if(nowp.getHP() <= ed1)
            return;
    }
    if(nowp.petAsleep()){
        os<<"Your "<<nowp.strType()<<" is sleeping"<<endl;
        return;
    }
    if(n == 1){
        switch(nowp.getType()) {
        case W:
            os<<"Your W uses Tackle! Damage: ";
            break;
        case L:
            os<<"Your L uses Claw! Damage: ";
            break;
        case G:
            os<<"Your G uses Tackle! Damage: ";
            break;
        case Q:
            os<<"Your Q uses Quick! Damage: ";
            break;
        case D:
            os<<"Your D uses Slap! Damage: ";
            break;
        default:
            assert(false);
        }
        os<<Damage(nowp, nowe, 1)<<endl;
        pd = 1;
        pd1 = Damage(nowp, nowe, 1);
        pski = 2;
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
        case Q:
            os<<"Your Q uses Volt! Damage: ";
            break;
        case D:
            os<<"Your D uses Sing! ";
            break;
        default:
            assert(false);
        }
        if(nowp.getType() != D){
            os<<Damage(nowp, nowe, 2)<<endl;
            pd = 2;
            pd1 = Damage(nowp, nowe, 2);
        }else{
            if(!nowe.petAsleep()){
                os<<"Enemy's "<<nowe.strType()<<" falls asleep"<<endl;
                nowe.fallAsleep();
                if(nowe.getType() == e1.getType()){
                    e1.fallAsleep();
                    bnum1 = 0;
                }
                else if(nowe.getType() == e2.getType()){
                    e2.fallAsleep();
                    bnum2 = 0;
                }
                else{
                    e3.fallAsleep();
                    bnum3 = 0;
                }
            }else
                os<<"Waste"<<endl;
        }
        pski = 2;
    }else{
        if(nowp.getType() == W){
            os<<"Your W uses Synthesis! Recovery: "<<Recovery()<<endl;
            nowp.rec(Recovery());
            if(np1.getType() == W)
                np1.rec(Recovery());
            else if(np2.getType() == W)
                np2.rec(Recovery());
            else
                np3.rec(Recovery());
            pski = 2;
        }else if(nowp.getType() == L){
            os<<"Your L uses Sunny! Weather becomes sunny"<<endl;
            w = 2;
            wnum = 0;
            pski = 2;
        }else if(nowp.getType() == G){
            os<<"Your L uses Rainy! Weather becomes rainy"<<endl;
            w = 3;
            wnum = 0;
            pski = 2;
        }else if(nowp.getType() == Q){
            os<<"Your Q uses Thunder! ";
            if(w == 3){
                os<<"Damage: "<<Damage(nowp, nowe, 3)<<endl;
                pd = 3;
                pd1 = Damage(nowp, nowe, 3);
                pski = 2;
            }else
                os<<"Failure"<<endl;
        }else{
            os<<"Your D uses Paint! ";
            if(eski == 2)
                os<<"Failure"<<endl;
            else{
                os<<"Enemy's "<<nowe.strType()<<" is painted"<<endl;
                nowe.bePainted();
                if(nowe.getType() == e1.getType())
                    e1.bePainted();
                else if(nowe.getType() == e2.getType())
                    e2.bePainted();
                else
                    e3.bePainted();
                pski = 2;
            }
        }
    }
    if(pd != 0){
        if(nowe.petAsleep()){
            nowe.awake();
            if(nowe.getType() == e1.getType())
                bnum1 = 0;
            else if(nowe.getType() == e2.getType())
                bnum2 = 0;
            else
                bnum3 = 0;
            if(nowe.petAlive() && nowe.getHP() > pd1)
                os<<"Enemy's "<<nowe.strType()<<" wakes up"<<endl;
        }
    }
}
//player choose a action
void selectAct(istream& is, ostream& os)
{
    bool flag = false;
    if(!is_alive(np1, np2) && nowp.getType() == np3.getType())
        os<<"Select your action (0 for escape, 1 for skill): ";
    else if(!is_alive(np1, np3) && nowp.getType() == np2.getType())
        os<<"Select your action (0 for escape, 1 for skill): ";
    else if(!is_alive(np2, np3) && nowp.getType() == np1.getType())
        os<<"Select your action (0 for escape, 1 for skill): ";
    else{
        os<<"Select your action (0 for escape, 1 for skill, 2 for change): ";
        flag = true;
    }
    int n;
    is >> n;
    if(n == 1)
        selectSki(is, os);
    else if(n == 2 && flag)
        nextPet(is, os);
    else if(n == 0)
        engine = false;
    else
        selectAct(is, os);
}
void showHP(ostream& os)
{
    PetType pt = nowp.getType();
    if(pt == np1.getType())
        os<<"Your "<<np1.strType()<<": HP "<<np1.getHP();
    else if(pt == np2.getType())
        os<<"Your "<<np2.strType()<<": HP "<<np2.getHP();
    else
        os<<"Your "<<np3.strType()<<": HP "<<np3.getHP();
    os<<" || ";
    switch(nowe.getType()) {
    case W:
        os<<"Enemy's W: HP "<<e1.getHP();
        break;
    case G:
        os<<"Enemy's G: HP "<<e2.getHP();
        break;
    case Q:
        os<<"Enemy's Q: HP "<<e3.getHP();
        break;
    default:
        assert(false);
    }
    os<<endl;
}
//the game's engine
void play(istream& is, ostream& os)
{
    //Before battle
    os<<"Welcome to Battle of Pets 2!"<<endl;
    os<<"Enemy has W,G and Q."<<endl;
    pTeam(is, os);
    srand(time(0));
    int enemy_start = rand() % 3 + 1;
    switch(enemy_start) {
    case 1:
        os<<"Enemy starts with W"<<endl;
        nowe = e1;
        break;
    case 2:
        os<<"Enemy starts with G"<<endl;
        nowe = e2;
        break;
    case 3:
        os<<"Enemy starts with Q"<<endl;
        nowe = e3;
        break;
    default:
        assert(false);
    }
    nowp = np1;
    showHP(os);
    os<<"Battle starts!"<<endl;

    //while in battle
    while(is)
    {
        for(int i = 1;i <= 50;i++)
            os<<"-";
        os<<endl;
        if(wnum == 5){
            os<<"Weather becomes normal"<<endl;
            wnum = 0;
            w = 1;
        }
        if(bnum1 == 3){
            os<<"Enemy's "<<nowe.strType()<<" wakes up"<<endl;
            nowe.awake();
            e1.awake();
            bnum1 = 0;
        }
        if(bnum2 == 3){
            os<<"Enemy's "<<nowe.strType()<<" wakes up"<<endl;
            nowe.awake();
            e2.awake();
            bnum2 = 0;
        }
        if(bnum3 == 3){
            os<<"Enemy's "<<nowe.strType()<<" wakes up"<<endl;
            nowe.awake();
            e3.awake();
            bnum3 = 0;
        }
        if(anum1 == 3){
            os<<"Your "<<nowp.strType()<<" wakes up"<<endl;
            nowp.awake();
            np1.awake();
            anum1 = 0;
        }
        if(anum2 == 3){
            os<<"Your "<<nowp.strType()<<" wakes up"<<endl;
            nowp.awake();
            np2.awake();
            anum2 = 0;
        }
        if(anum3 == 3){
            os<<"Your "<<nowp.strType()<<" wakes up"<<endl;
            nowp.awake();
            np3.awake();
            anum3 = 0;
        }
        os<<"Round "<<rnum<<endl;
        pski = eski = 1;
        pd = ed = pd1 = ed1 = 0;
        selectAct(is, os);
        PetType et = nowe.getType();
        if(!nowe.petAlive()){
            switch(nowe.getType()) {
            case W:
                os<<"Enemy's W is beaten"<<endl;
                break;
            case G:
                os<<"Enemy's G is beaten"<<endl;
                break;
            case Q:
                os<<"Enemy's Q is beaten"<<endl;
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
                    case Q:
                        os<<"Your Q is beaten"<<endl;
                        break;
                    case D:
                        os<<"Your D is beaten"<<endl;
                        break;
                    default:
                        assert(false);
                    }
                    if(np1.petAlive() || np2.petAlive() || np3.petAlive())
                        changePet(is, os);
                }
                if(np1.petAlive() || np2.petAlive() || np3.petAlive())
                    os<<"You Win"<<endl;
                else
                    os<<"Draw"<<endl;
                break;
            }
            et = enemy_nextpet();
        }else{
            if(nowe.petAsleep()){
                if(nowe.getType() == W)
                    bnum1++;
                else if(nowe.getType() == G)
                    bnum2++;
                else
                    bnum3++;
            }
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
            case Q:
                os<<"Your Q is beaten"<<endl;
                break;
            case D:
                os<<"Your D is beaten"<<endl;
                break;
            default:
                assert(false);
            }
            if(!np1.petAlive() && !np2.petAlive() && !np3.petAlive()){
                if(et != nowe.getType()){
                    switch(et) {
                    case W:
                        os<<"Enemy sends W"<<endl;
                        break;
                    case G:
                        os<<"Enemy sends G"<<endl;
                        break;
                    case Q:
                        os<<"Enemy sends Q"<<endl;
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
        }else{
            if(nowp.petAsleep()){
                if(nowp.getType() == np1.getType())
                    anum1++;
                else if(nowp.getType() == np2.getType())
                    anum2++;
                else
                    anum3++;
            }
        }
        if(et != nowe.getType()){
            switch(et) {
            case W:
                os<<"Enemy sends W"<<endl;
                nowe = e1;
                break;
            case G:
                os<<"Enemy sends G"<<endl;
                nowe = e2;
                break;
            case Q:
                os<<"Enemy sends Q"<<endl;
                nowe = e3;
                break;
            default:
                assert(false);
            }
        }

        if(w > 1)
            wnum++;
        if(!engine){
            os<<"You Escape"<<endl;
            break;
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
    p1.petInfo(), p2.petInfo(), p3.petInfo(), p4.petInfo(), p5.petInfo();
    e1.petInfo(), e2.petInfo(), e3.petInfo();
    play(cin, cout);
    return 0;
}
