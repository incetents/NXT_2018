
#include "stdafx.h"

#include "MatrixStack.h"

_MatrixStack& _MatrixStack::pushMatrix(const Matrix4x4& matrix)
{
	assert(m_size < 255);

	if (m_size == 0)
		m_stack.push(matrix);
	else
		m_stack.push(m_stack.top() * matrix);

	m_size++;
	return *this;
}
_MatrixStack& _MatrixStack::popMatrix()
{
	if (m_size == 0)
		return * this;

	m_stack.pop();

	m_size--;
	return *this;
}
Matrix4x4 _MatrixStack::getState()
{
	if (m_size == 0)
		return Matrix4x4();

	return m_stack.top();
}