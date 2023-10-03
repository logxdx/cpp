/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "ulimitedrational.h"

UnlimitedInt* GCD(UnlimitedInt* i1, UnlimitedInt* i2) {
    
    UnlimitedInt* temp1 = new UnlimitedInt(i1->to_string());
    UnlimitedInt* temp2 = new UnlimitedInt(i2->to_string());

    while (temp2->get_sign() != 0) {
        UnlimitedInt* temp = temp2;
        temp2 = UnlimitedInt::mod(temp1, temp2);
        delete temp1;
        temp1 = temp;
    }

    return temp1;
}

UnlimitedRational::UnlimitedRational() {
    p = new UnlimitedInt(0);
    q = new UnlimitedInt(1);
}

UnlimitedRational::UnlimitedRational(UnlimitedInt* num, UnlimitedInt* den) {

    if (den->get_sign() == 0) {
        p = new UnlimitedInt(0);
        q = new UnlimitedInt(0);
    }

    else {

        if (num->get_sign() == 0) {
            p = new UnlimitedInt(0);
            q = den;
        }
        
        else {
            UnlimitedInt* gcd = GCD(num, den);

            // cout<<"NUM : "<<num->to_string()<<endl;
            // cout<<"DEN : "<<den->to_string()<<endl;
            // cout<<"GCD : "<<gcd->to_string()<<endl;
            
            p = UnlimitedInt::div(num, gcd);
            q = UnlimitedInt::div(den, gcd);
        }
    }
}

UnlimitedRational::~UnlimitedRational() {
    delete p;
    delete q;
}

UnlimitedInt* UnlimitedRational::get_p() {
    return p;
}

UnlimitedInt* UnlimitedRational::get_q() {
    return q;
}

string UnlimitedRational::get_p_str() {
    return p->to_string();
}

string UnlimitedRational::get_q_str() {
    return q->to_string();
}

string UnlimitedRational::get_frac_str() {
    return p->to_string() + "/" + q->to_string();
}

UnlimitedRational* UnlimitedRational::add(UnlimitedRational* i1, UnlimitedRational* i2) {

    if (i1->get_frac_str() == "0/0" || i2->get_frac_str() == "0/0") {
        return i1;
    }

    UnlimitedInt *a, *b;

    a = UnlimitedInt::add(UnlimitedInt::mul(i1->p, i2->q), UnlimitedInt::mul(i1->q, i2->p));
    b = UnlimitedInt::mul(i1->q, i2->q);

    return new UnlimitedRational(a, b);
}

UnlimitedRational* UnlimitedRational::sub(UnlimitedRational* i1, UnlimitedRational* i2) {

    if (i1->get_frac_str() == "0/0" || i2->get_frac_str() == "0/0") {
        return i1;
    }

    UnlimitedInt *a, *b;

    a = UnlimitedInt::sub(UnlimitedInt::mul(i1->p, i2->q), UnlimitedInt::mul(i1->q, i2->p));
    b = UnlimitedInt::mul(i1->q, i2->q);

    return new UnlimitedRational(a, b);
  
}

UnlimitedRational* UnlimitedRational::mul(UnlimitedRational* i1, UnlimitedRational* i2) {

    if (i1->get_frac_str() == "0/0") {
        return i1;
    }

    if (i2->get_frac_str() == "0/0") {
        return i2;
    }

    UnlimitedInt *a, *b;

    a = UnlimitedInt::mul(i1->p, i2->p);
    b = UnlimitedInt::mul(i1->q, i2->q);

    return new UnlimitedRational(a, b);
}

UnlimitedRational* UnlimitedRational::div(UnlimitedRational* i1, UnlimitedRational* i2) {

    if (i1->get_frac_str() == "0/0") {
        return i1;
    }

    if (i2->get_frac_str() == "0/0") {
        return i2;
    }

    UnlimitedInt *a, *b;

    a = UnlimitedInt::mul(i1->p, i2->q);
    b = UnlimitedInt::mul(i1->q, i2->p);

    return new UnlimitedRational(a, b);
}
