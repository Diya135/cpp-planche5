#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;
//Exercice 1:
class Etudiant {
private:
    static int idCounter;
    int matricule;
    string nom;
    vector<float> tabNotes;

public:
    Etudiant() : matricule(++idCounter), nom(""), tabNotes() {}
    Etudiant(string name) : matricule(++idCounter), nom(name), tabNotes() {}
    ~Etudiant() {}
    Etudiant(const Etudiant &e) : matricule(e.matricule), nom(e.nom), tabNotes(e.tabNotes) {}
    void setNom(string name) { nom = name; }
    string getNom() const { return nom; }

    void saisie() {
        int nbr;
        cout<<"Enter number of notes: ";
        cin >> nbr;
        tabNotes.resize(nbr);
        for (int i = 0; i < nbr; ++i) {
            cout<<"Enter note "<<(i + 1)<<": ";
            cin >> tabNotes[i];
        }
    }

    void affichage() const {
        cout<<"Matricule: "<<matricule<<", Nom: "<<nom<<", Notes: ";
        for (float note : tabNotes) {
            cout<<note<<" ";
        }
        cout<<endl;
    }

    float moyenne() const {
        float sum = 0;
        for (float note : tabNotes) {
            sum += note;
        }
        return sum / tabNotes.size();
    }

    bool admis() const {
        return moyenne() >= 10;
    }

    static bool comparer(const Etudiant &e1, const Etudiant &e2) {
        return e1.moyenne() == e2.moyenne();
    }
};

int Etudiant::idCounter = 0;
//Exercise 2:
class Vecteur3D {
private:
    float x, y, z;

public:
    Vecteur3D(float x = 0, float y = 0, float z = 0) : x(x), y(y), z(z) {}
    void afficher() const {
        cout<<"("<<x<<", "<<y<<", "<<z<<")"<<endl;
    }
    Vecteur3D somme(const Vecteur3D &v) const {
        return Vecteur3D(x + v.x, y + v.y, z + v.z);
    }
    float produitScalaire(const Vecteur3D &v) const {
        return x * v.x + y * v.y + z * v.z;
    }
    bool coincide(const Vecteur3D &v) const {
        return (x == v.x && y == v.y && z == v.z);
    }

    float norme() const {
        return sqrt(x * x + y * y + z * z);
    }

    static Vecteur3D normax(const Vecteur3D &v1, const Vecteur3D &v2) {
        return (v1.norme() > v2.norme()) ? v1 : v2;
    }
};
//Exercice 3:

class Point {
private:
    float x, y;

public:
    Point(float x = 0, float y = 0) : x(x), y(y) {}
    Point(const Point &p) : x(p.x), y(p.y) {}
    void affiche() const {
        cout<<"Point("<<x<<", "<<y<<")"<<endl;
    }
    friend bool comparer(const Point &p1, const Point &p2) {
        return (p1.x == p2.x && p1.y == p2.y);
    }

    friend float distance(const Point &p1, const Point &p2) {
        return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));
    }

    friend Point milieu(const Point &p1 , const Point &p2) {
        return Point((p1.x + p2.x) / 2, (p1.y + p2.y) / 2);
    }
};
//Exercice 4:
class Complexe {
private:
    double Re, Img;

public:
    Complexe(double re = 0, double img = 0) : Re(re), Img(img) {}
    void afficher() const {
        cout<<Re<<" + "<<Img<<"i"<<endl;
    }
    double module() const {
        return sqrt(Re * Re + Img * Img);
    }
    Complexe conjugue() const {
        return Complexe(Re, -Img);
    }
    Complexe operator+(const Complexe &c) const {
        return Complexe(Re + c.Re, Img + c.Img);
    }

    Complexe operator+(double d) const {
        return Complexe(Re + d, Img);
    }

    friend Complexe operator+(double d, const Complexe &c) {
        return Complexe(d + c.Re, c.Img);
    }

    Complexe operator*(const Complexe &c) const {
        return Complexe(Re * c.Re - Img * c.Img, Re * c.Img + Img * c.Re);
    }

    Complexe operator-(const Complexe &c) const {
        return Complexe(Re - c.Re, Img - c.Img);
    }
};
//Exercice 5:
class Point;

class Cercle {
private:
    float rayon;
    Point centre;

public:
    Cercle(float r, const Point &c) : rayon(r), centre(c) {}
    Cercle(float r, float x, float y) : rayon(r), centre(Point(x, y)) {}
    void afficher() const {
        cout<<"Cercle: Rayon = "<<rayon<<", Centre = ";
        centre.affiche();
    }
    float getRayon() const { return rayon; }
    void setRayon(float r) { rayon = r; }
    float surface() const {
        return M_PI * rayon * rayon;
    }

    float perimetre() const {
        return 2 * M_PI * rayon;
    }
    bool egal(const Cercle &c) const {
        return (rayon == c.rayon && centre == c.centre);
    }
    bool appartient(const Point &p) const;
};
class Point {
private:
    float x, y;

public:
    Point(float x = 0, float y = 0) : x(x), y(y) {}
    void affiche() const {
        cout<<"Point("<<x<<", "<<y<<")"<<endl;
    }
    bool operator==(const Point &p) const {
        return (x == p.x && y == p.y);
    }
    float getX() const { return x; }
    float getY() const { return y; }
};
bool Cercle::appartient(const Point &p) const {
    float distance = sqrt(pow(p.getX() - centre.getX(), 2) + pow(p.getY() - centre.getY(), 2));
    return distance <= rayon;
}
//main:
int main() {
    //Exercise 1
    Etudiant e1("Alice");
    e1.saisie();
    e1.affichage();
    cout<<"Moyenne: "<<e1.moyenne()<<", Admis: "<<(e1.admis() ? "Oui" : "Non")<<endl;

    //Exercise 2
    Vecteur3D v1(1, 2, 3), v2(4, 5, 6);
    v1.afficher();
    v2.afficher();
    Vecteur3D v3 = v1.somme(v2);
    v3.afficher();
    cout<<"Produit scalaire: "<<v1.produitScalaire(v2)<<endl;
    cout<<"Norme de v1: "<<v1.norme()<<endl;

    //Exercise 3
    Point p1(1, 2), p2(3, 4);
    p1.affiche();
    p2.affiche();
    cout<<"Distance entre p1 et p2: "<< distance(p1, p2)<<endl;
    Point milieuPoint = milieu(p1, p2);
    milieuPoint.affiche();

    //Exercise 4
    Complexe c1(1, 2), c2(3, 4);
    c1.afficher();
    c2.afficher();
    Complexe c3 = c1 + c2;
    c3.afficher();
    cout<<"Module de c1: "<<c1.module()<<endl;

    //Exercise 5
    Cercle cercle(5, Point(10, 10));
    cercle.afficher();
    cout<<"Surface: "<<cercle.surface()<<", Périmètre: "<<cercle.perimetre()<<endl;
    cercle.setRayon(10);
    cercle.afficher();
    Point p3(10, 10);
    cout<<"Point (10, 10) appartient au cercle: "<<(cercle.appartient(p3) ? "Oui" : "Non")<<endl;

    return 0;
}