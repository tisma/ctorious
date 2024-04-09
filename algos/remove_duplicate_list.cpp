#include <iostream>
#include <memory>


struct ListNode {
	int val;
	std::unique_ptr<ListNode> next;
	ListNode(int x) : val(x), next(nullptr) {}
};

void printLinkedList(const ListNode* head) {
    while (head != nullptr) {
        std::cout << head->val << " ";
        head = head->next.get();
    }
    std::cout << std::endl;
}

std::unique_ptr<ListNode> deleteDuplicates(std::unique_ptr<ListNode> head) {
	std::unique_ptr<ListNode> dummy = std::make_unique<ListNode>(0);
	dummy->next = std::move(head);
	ListNode* prev = dummy.get();
	ListNode* curr = dummy->next.get();

	while (curr != nullptr) {
		bool isDuplicate = false;
		while (curr->next != nullptr && curr->val == curr->next->val) {
			curr = curr->next.get();
			isDuplicate = true;
		}

		if (isDuplicate) {
			prev->next = std::move(curr->next);
			curr = prev->next.get();
		} else {
			prev = curr;
			curr = curr->next.get();
		}
	}

	return std::move(dummy->next);
}

int main() {
    // Example input: 1 -> 2 -> 3 -> 3 -> 4 -> 4 -> 5
    std::unique_ptr<ListNode> head = std::make_unique<ListNode>(1);
    head->next = std::make_unique<ListNode>(2);
    head->next->next = std::make_unique<ListNode>(3);
    head->next->next->next = std::make_unique<ListNode>(3);
    head->next->next->next->next = std::make_unique<ListNode>(4);
    head->next->next->next->next->next = std::make_unique<ListNode>(4);
    head->next->next->next->next->next->next = std::make_unique<ListNode>(5);

    std::cout << "Original linked list: ";
    printLinkedList(head.get());

    auto newHead = deleteDuplicates(std::move(head));

    std::cout << "Linked list after removing duplicates: ";
    printLinkedList(newHead.get());

    return 0;
}

