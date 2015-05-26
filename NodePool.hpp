#ifndef NODEPOOL_HPP
# define NODEPOOL_HPP

# include <stack>
# include "Node.hpp"

class NodePool {
public:
	NodePool(void);
	NodePool(size_t size);
	~NodePool(void);
	NodePool(const NodePool& src);

	NodePool&	operator=(const NodePool& rhs);

	void		allocateNodes(size_t number);
	Node*		newNode(void);
	void		delNode(Node*);

private:
	std::stack<Node*>	freeNodes;
	size_t				size;
};

#endif // NODEPOOL_HPP
