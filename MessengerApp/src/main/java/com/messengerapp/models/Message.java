package com.messengerapp.models;

import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.UUID;

/**
 * Abstract base class for all message types.
 * Demonstrates polymorphism through different message implementations.
 */
public abstract class Message {
    private String id;
    private String senderId;
    private String receiverId;
    private LocalDateTime timestamp;
    private MessageStatus status;
    
    /**
     * Enum representing message delivery status
     */
    public enum MessageStatus {
        SENT, DELIVERED, READ, FAILED
    }
    
    /**
     * Constructor for Message
     * @param senderId ID of the message sender
     * @param receiverId ID of the message receiver
     */
    public Message(String senderId, String receiverId) {
        this.id = UUID.randomUUID().toString();
        this.senderId = senderId;
        this.receiverId = receiverId;
        this.timestamp = LocalDateTime.now();
        this.status = MessageStatus.SENT;
    }
    
    // Abstract method to be implemented by subclasses
    public abstract String getContent();
    public abstract String getMessageType();
    public abstract void displayMessage();
    
    // Getters and Setters
    public String getId() {
        return id;
    }
    
    public void setId(String id) {
        this.id = id;
    }
    
    public String getSenderId() {
        return senderId;
    }
    
    public void setSenderId(String senderId) {
        this.senderId = senderId;
    }
    
    public String getReceiverId() {
        return receiverId;
    }
    
    public void setReceiverId(String receiverId) {
        this.receiverId = receiverId;
    }
    
    public LocalDateTime getTimestamp() {
        return timestamp;
    }
    
    public void setTimestamp(LocalDateTime timestamp) {
        this.timestamp = timestamp;
    }
    
    public MessageStatus getStatus() {
        return status;
    }
    
    public void setStatus(MessageStatus status) {
        this.status = status;
    }
    
    /**
     * Get formatted timestamp string
     * @return formatted timestamp
     */
    public String getFormattedTimestamp() {
        DateTimeFormatter formatter = DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm:ss");
        return timestamp.format(formatter);
    }
    
    /**
     * Mark message as delivered
     */
    public void markAsDelivered() {
        this.status = MessageStatus.DELIVERED;
    }
    
    /**
     * Mark message as read
     */
    public void markAsRead() {
        this.status = MessageStatus.READ;
    }
    
    @Override
    public String toString() {
        return String.format("Message{id='%s', type='%s', from='%s', to='%s', timestamp='%s', status=%s}", 
                           id, getMessageType(), senderId, receiverId, getFormattedTimestamp(), status);
    }
}