#include <poincare/opposite.h>
#include <poincare/complex_matrix.h>
#include <poincare/complex.h>
#include <poincare/multiplication.h>
#include <poincare/rational.h>
extern "C" {
#include <assert.h>
#include <stdlib.h>
}
#include <cmath>
#include "layout/horizontal_layout.h"
#include "layout/parenthesis_layout.h"
#include "layout/string_layout.h"

namespace Poincare {

Expression::Type Opposite::type() const {
  return Type::Opposite;
}

Expression * Opposite::clone() const {
  Opposite * o = new Opposite(m_operands, true);
  return o;
}

template<typename T>
Complex<T> Opposite::compute(const Complex<T> c, AngleUnit angleUnit) {
  return Complex<T>::Cartesian(-c.a(), -c.b());
}

Expression * Opposite::immediateSimplify() {
  const Expression * multOperands[2] = {new Rational(Integer(-1)), operand(0)};
  detachOperand(operand(0));
  Multiplication * m = new Multiplication(multOperands, 2, false);
  replaceWith(m, true);
  return m->immediateSimplify();
}

ExpressionLayout * Opposite::privateCreateLayout(FloatDisplayMode floatDisplayMode, ComplexFormat complexFormat) const {
  assert(floatDisplayMode != FloatDisplayMode::Default);
  assert(complexFormat != ComplexFormat::Default);
  ExpressionLayout * children_layouts[2];
  char string[2] = {'-', '\0'};
  children_layouts[0] = new StringLayout(string, 1);
  children_layouts[1] = operand(0)->type() == Type::Opposite ? new ParenthesisLayout(operand(0)->createLayout(floatDisplayMode, complexFormat)) : operand(0)->createLayout(floatDisplayMode, complexFormat);
  return new HorizontalLayout(children_layouts, 2);
}

}

template Poincare::Complex<float> Poincare::Opposite::compute<float>(Poincare::Complex<float>, AngleUnit angleUnit);
template Poincare::Complex<double> Poincare::Opposite::compute<double>(Poincare::Complex<double>, AngleUnit angleUnit);
