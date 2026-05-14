// DOM Elements
const chatWindow = document.getElementById('chat-window');
const userInput = document.getElementById('user-input');
const sendBtn = document.getElementById('send-btn');

// Rule-based logic for chatbot responses
function getBotResponse(input) {
    const text = input.toLowerCase();

    // Greeting rules
    if (text.includes("hello") || text.includes("hi") || text.includes("hey")) {
        return "Hello there! How can I assist you with our tech products today?";
    }
    
    // Product queries
    else if (text.includes("laptop") || text.includes("computer")) {
        return "We have a variety of laptops including the Laptop Pro X. Are you looking for gaming or business laptops?";
    } 
    else if (text.includes("phone") || text.includes("smartphone")) {
        return "Our Smartphone Z is currently on sale! Would you like to know its specs?";
    }
    else if (text.includes("earbuds") || text.includes("headphones") || text.includes("audio")) {
        return "Our Wireless Earbuds offer active noise cancellation and 24 hours of battery life. They cost $99.";
    }
    
    // Store information
    else if (text.includes("time") || text.includes("hours") || text.includes("open")) {
        return "Our store is open 24/7 online! Customer support is available 9 AM to 9 PM daily.";
    }
    else if (text.includes("shipping") || text.includes("delivery")) {
        return "We offer free standard shipping on orders over $50. Deliveries usually take 3-5 business days.";
    }
    
    // Farewell rules
    else if (text.includes("bye") || text.includes("thanks") || text.includes("thank you")) {
        return "You're welcome! Have a great day and thanks for visiting Tech G-Store!";
    }
    
    // Default fallback
    else {
        return "I'm sorry, I didn't quite catch that. You can ask me about our laptops, phones, earbuds, store hours, or shipping!";
    }
}

// Function to add a message to the chat window
function addMessage(messageText, sender) {
    // Create new div for the message
    const messageElement = document.createElement('div');
    messageElement.classList.add('message');
    
    // Distinguish between user and bot visually
    if (sender === 'user') {
        messageElement.classList.add('user-message');
    } else {
        messageElement.classList.add('bot-message');
    }
    
    messageElement.textContent = messageText;
    
    // Append and scroll to the bottom
    chatWindow.appendChild(messageElement);
    chatWindow.scrollTop = chatWindow.scrollHeight;
}

// Handle sending message
function handleSend() {
    const text = userInput.value.trim();
    if (text === '') return; // Don't send empty messages

    // 1. Show user message
    addMessage(text, 'user');
    
    // 2. Clear input field
    userInput.value = '';

    // 3. Get and show bot response with a slight delay to simulate typing
    setTimeout(() => {
        const botResponse = getBotResponse(text);
        addMessage(botResponse, 'bot');
    }, 500); // 500ms delay
}

// Event Listeners for click and 'Enter' key
sendBtn.addEventListener('click', handleSend);

userInput.addEventListener('keypress', function(e) {
    if (e.key === 'Enter') {
        handleSend();
    }
});