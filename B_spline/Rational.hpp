#pragma once
#ifdef SPARSE_INTERP_WITH_GMP
#include <gmp.h>
#include <iostream>



	class Rational
	{ 
	public:
		mpq_t value;
		void canonicalize()
		{
			mpq_canonicalize(value);
		}
		int get_sign()
		{
			return mpq_sgn(value);
		}

		Rational()
		{
			mpq_init(value);
			mpq_set_d(value, 0);
		}

		Rational(double d)
		{
			mpq_init(value);
			mpq_set_d(value, d);
			//            canonicalize();
		}

		Rational(const mpq_t &v_)
		{
			mpq_init(value);
			mpq_set(value, v_);
			//            canonicalize();
		}

		Rational(const Rational &other)
		{
			mpq_init(value);
			mpq_set(value, other.value);
		}

		~Rational()
		{
			mpq_clear(value);
		}

		//        //+, - another point
		//        Rational operator+(const Rational &r) const {
		//            Rational r_out;
		//            mpq_add(r_out.value, value, r.value);
		//            return r_out;
		//        }
		//
		//        Rational operator-(const Rational &r) const {
		//            Rational r_out;
		//            mpq_sub(r_out.value, value, r.value);
		//            return r_out;
		//        }
		//
		//        //*, / double/rational
		//        Rational operator*(const Rational &r) const {
		//            Rational r_out;
		//            mpq_mul(r_out.value, value, r.value);
		//            return r_out;
		//        }
		//
		//        Rational operator/(const Rational &r) const {
		//            Rational r_out;
		//            mpq_div(r_out.value, value, r.value);
		//            return r_out;
		//        }
		//
		//        //=
		//        void operator=(const Rational &r) {
		//            mpq_set(value, r.value);
		//        }

		friend Rational operator+(const Rational &x, const Rational &y)
		{
			Rational r_out;
			mpq_add(r_out.value, x.value, y.value);
			return r_out;
		}

		friend Rational operator-(const Rational &x, const Rational &y)
		{
			Rational r_out;
			mpq_sub(r_out.value, x.value, y.value);
			return r_out;
		}

		friend Rational operator*(const Rational &x, const Rational &y)
		{
			Rational r_out;
			mpq_mul(r_out.value, x.value, y.value);
			return r_out;
		}

		friend Rational operator/(const Rational &x, const Rational &y)
		{
			Rational r_out;
			mpq_div(r_out.value, x.value, y.value);
			return r_out;
		}

		Rational &operator=(const Rational &x)
		{
			if (this == &x)
				return *this;
			mpq_set(value, x.value);
			return *this;
		}
		
		Rational &operator=(const double x)
		{
			mpq_set_d(value, x);
			//            canonicalize();
			return *this;
		}

		////////////// TODO not sure if this works
		friend Rational operator -(const Rational &b) {
			Rational r = Rational(-1)*b;
			return r;
		}
		Rational &operator /=(const Rational &x)
		{
			Rational r_out;
			mpq_div(value, value, x.value);// value = value / x.value
			return *this;
		}
		Rational &operator -=(const Rational &x)
		{
			Rational r_out;
			mpq_sub(value, value, x.value);// value = value / x.value
			return *this;
		}
		////////////////////
		//> < ==
		friend bool operator<(const Rational &r, const Rational &r1)
		{
			return mpq_cmp(r.value, r1.value) < 0;
		}

		friend bool operator>(const Rational &r, const Rational &r1)
		{
			return mpq_cmp(r.value, r1.value) > 0;
		}

		friend bool operator<=(const Rational &r, const Rational &r1)
		{
			return mpq_cmp(r.value, r1.value) <= 0;
		}

		friend bool operator>=(const Rational &r, const Rational &r1)
		{
			return mpq_cmp(r.value, r1.value) >= 0;
		}

		friend bool operator==(const Rational &r, const Rational &r1)
		{
			return mpq_equal(r.value, r1.value);
		}

		friend bool operator!=(const Rational &r, const Rational &r1)
		{
			return !mpq_equal(r.value, r1.value);
		}

		//to double
		double to_double()
		{
			return mpq_get_d(value);
		}

		//<<
		friend std::ostream &operator<<(std::ostream &os, const Rational &r)
		{
			os << mpq_get_d(r.value);
			return os;
		}
	};


#endif 