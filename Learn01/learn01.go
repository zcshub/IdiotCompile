package learn01

import "fmt"

/////////////////////////////////////////////////////
///// 模拟一个树结构

type NodeKind uint8

const (
	NodeKind_Int NodeKind = 0
	NodeKind_Add NodeKind = 1
)

type NodeInt struct {
	kind  NodeKind
	value int
}

type NodeAdd struct {
	kind  NodeKind
	left  interface{}
	right interface{}
}

func newIntNode(value int) *NodeInt {
	return &NodeInt{
		NodeKind_Int,
		value,
	}
}

func newAddNode(left, right interface{}) *NodeAdd {
	return &NodeAdd{
		NodeKind_Add,
		left,
		right,
	}
}

func printTree(root interface{}) {
	switch v := root.(type) {
	case *NodeInt:
		fmt.Print(v.value)
	case *NodeAdd:
		printTree(v.left)
		fmt.Print("+")
		printTree(v.right)
	}
}

/////////////////////////////////////////////////////
///// 模拟一个指令结构

type Instruction uint8

const (
	Instruction_Push Instruction = 0
	Instruction_Add  Instruction = 1
)

type InstructionPush struct {
	value int
}

type InstructionAdd struct {
}

type InstructionStack struct {
	stack []interface{}
}

func (s *InstructionStack) Push(i interface{}) {
	s.stack = append(s.stack, i)
}

func (s *InstructionStack) Pop() interface{} {
	e := s.stack[len(s.stack)-1]
	s.stack = s.stack[0 : len(s.stack)-1]
	return e
}

func (s *InstructionStack) Top() interface{} {
	return s.stack[len(s.stack)-1]
}

func postOrder(stack *InstructionStack, node interface{}) {
	switch v := node.(type) {
	case *NodeInt:
		stack.Push(&InstructionPush{v.value})
	case *NodeAdd:
		postOrder(stack, v.left)
		postOrder(stack, v.right)
		stack.Push(&InstructionAdd{})
	}
}

func compile(root *NodeAdd) *InstructionStack {
	stack := &InstructionStack{stack: make([]interface{}, 0)}
	postOrder(stack, root)
	return stack
}

func printStack(stack *InstructionStack) {
	for _, i := range stack.stack {
		switch v := i.(type) {
		case *InstructionPush:
			fmt.Printf("Push %d\n", v.value)
		case *InstructionAdd:
			fmt.Println("Add")
		}
	}
}

/////////////////////////////////////////////////////

/////////////////////////////////////////////////////

func App() {
	// 目前还没有学习语法书构建，直接手动创建一个
	root := newAddNode(newAddNode(newIntNode(1), newIntNode(2)), newIntNode(3))
	printTree(root)
	fmt.Println()
	stack := compile(root)
	printStack(stack)
}
