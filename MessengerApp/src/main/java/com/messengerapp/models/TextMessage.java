package com.messengerapp.models;

/**
 * TextMessage implementation of Message.
 * Represents a simple text message between users.
 */
public class TextMessage extends Message {
    private String textContent;
    
    /**
     * Constructor for TextMessage
     * @param senderId ID of the sender
     * @param receiverId ID of the receiver
     * @param textContent The text content of the message
     */
    public TextMessage(String senderId, String receiverId, String textContent) {
        super(senderId, receiverId);
        this.textContent = textContent;
    }
    
    @Override
    public String getContent() {
        return textContent;
    }
    
    @Override
    public String getMessageType() {
        return "TEXT";
    }
    
    @Override
    public void displayMessage() {
        System.out.println("[" + getFormattedTimestamp() + "] Text: " + textContent);
    }
    
    /**
     * Set the text content
     * @param textContent The new text content
     */
    public void setTextContent(String textContent) {
        this.textContent = textContent;
    }
    
    /**
     * Get the length of the text message
     * @return length of text content
     */
    public int getLength() {
        return textContent != null ? textContent.length() : 0;
    }
    
    /**
     * Check if message is empty
     * @return true if message is empty or null
     */
    public boolean isEmpty() {
        return textContent == null || textContent.trim().isEmpty();
    }
}