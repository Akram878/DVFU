package com.messengerapp.models;

import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.List;
import java.util.UUID;
import java.util.stream.Collectors;

/**
 * Represents a chat conversation between two or more users.
 * Manages messages and participants in the conversation.
 */
public class Chat {
    private String chatId;
    private String chatName;
    private List<String> participantIds;
    private List<Message> messages;
    private LocalDateTime createdAt;
    private LocalDateTime lastActivity;
    private ChatType chatType;
    
    /**
     * Enum representing different chat types
     */
    public enum ChatType {
        PRIVATE, // 1-on-1 chat
        GROUP    // Group chat with multiple participants
    }
    
    /**
     * Constructor for private chat between two users
     * @param user1Id First user ID
     * @param user2Id Second user ID
     */
    public Chat(String user1Id, String user2Id) {
        this.chatId = UUID.randomUUID().toString();
        this.participantIds = new ArrayList<>();
        this.participantIds.add(user1Id);
        this.participantIds.add(user2Id);
        this.messages = new ArrayList<>();
        this.createdAt = LocalDateTime.now();
        this.lastActivity = LocalDateTime.now();
        this.chatType = ChatType.PRIVATE;
        this.chatName = "Private Chat";
    }
    
    /**
     * Constructor for group chat
     * @param chatName Name of the group chat
     * @param participantIds List of participant user IDs
     */
    public Chat(String chatName, List<String> participantIds) {
        this.chatId = UUID.randomUUID().toString();
        this.chatName = chatName;
        this.participantIds = new ArrayList<>(participantIds);
        this.messages = new ArrayList<>();
        this.createdAt = LocalDateTime.now();
        this.lastActivity = LocalDateTime.now();
        this.chatType = participantIds.size() > 2 ? ChatType.GROUP : ChatType.PRIVATE;
    }
    
    /**
     * Add a message to the chat
     * @param message The message to add
     * @return true if message was added successfully
     */
    public boolean addMessage(Message message) {
        if (message == null) {
            return false;
        }
        
        // Verify sender is a participant
        if (!participantIds.contains(message.getSenderId())) {
            return false;
        }
        
        // For private chats, verify receiver is the other participant
        if (chatType == ChatType.PRIVATE && !participantIds.contains(message.getReceiverId())) {
            return false;
        }
        
        messages.add(message);
        lastActivity = LocalDateTime.now();
        return true;
    }
    
    /**
     * Add a participant to the chat (for group chats)
     * @param userId The user ID to add
     * @return true if user was added successfully
     */
    public boolean addParticipant(String userId) {
        if (userId == null || participantIds.contains(userId)) {
            return false;
        }
        
        participantIds.add(userId);
        
        // Update chat type if needed
        if (participantIds.size() > 2) {
            chatType = ChatType.GROUP;
        }
        
        lastActivity = LocalDateTime.now();
        return true;
    }
    
    /**
     * Remove a participant from the chat
     * @param userId The user ID to remove
     * @return true if user was removed successfully
     */
    public boolean removeParticipant(String userId) {
        if (userId == null || !participantIds.contains(userId)) {
            return false;
        }
        
        // Don't allow removing participants if it would leave less than 2
        if (participantIds.size() <= 2) {
            return false;
        }
        
        participantIds.remove(userId);
        lastActivity = LocalDateTime.now();
        return true;
    }
    
    /**
     * Get all messages in the chat
     * @return List of messages
     */
    public List<Message> getMessages() {
        return new ArrayList<>(messages);
    }
    
    /**
     * Get messages from a specific sender
     * @param senderId The sender's user ID
     * @return List of messages from the sender
     */
    public List<Message> getMessagesFromSender(String senderId) {
        return messages.stream()
                .filter(msg -> msg.getSenderId().equals(senderId))
                .collect(Collectors.toList());
    }
    
    /**
     * Get the most recent message
     * @return The last message or null if no messages
     */
    public Message getLastMessage() {
        return messages.isEmpty() ? null : messages.get(messages.size() - 1);
    }
    
    /**
     * Get unread messages for a specific user
     * @param userId The user ID
     * @return List of unread messages for the user
     */
    public List<Message> getUnreadMessages(String userId) {
        return messages.stream()
                .filter(msg -> !msg.getSenderId().equals(userId) && 
                              msg.getStatus() != Message.MessageStatus.READ)
                .collect(Collectors.toList());
    }
    
    /**
     * Mark all messages as read for a specific user
     * @param userId The user ID
     */
    public void markAllAsRead(String userId) {
        messages.stream()
                .filter(msg -> !msg.getSenderId().equals(userId))
                .forEach(Message::markAsRead);
    }
    
    /**
     * Display all messages in the chat
     */
    public void displayMessages() {
        System.out.println("\n=== " + chatName + " ===");
        System.out.println("Participants: " + participantIds.size());
        System.out.println("Messages: " + messages.size());
        System.out.println("Type: " + chatType);
        System.out.println("---");
        
        if (messages.isEmpty()) {
            System.out.println("No messages yet.");
        } else {
            for (Message message : messages) {
                System.out.print("[" + message.getSenderId() + "] ");
                message.displayMessage();
            }
        }
        System.out.println("=================\n");
    }
    
    /**
     * Check if a user is a participant in this chat
     * @param userId The user ID to check
     * @return true if user is a participant
     */
    public boolean isParticipant(String userId) {
        return participantIds.contains(userId);
    }
    
    /**
     * Get the number of messages in the chat
     * @return Number of messages
     */
    public int getMessageCount() {
        return messages.size();
    }
    
    /**
     * Get the number of participants
     * @return Number of participants
     */
    public int getParticipantCount() {
        return participantIds.size();
    }
    
    // Getters and Setters
    public String getChatId() {
        return chatId;
    }
    
    public String getChatName() {
        return chatName;
    }
    
    public void setChatName(String chatName) {
        this.chatName = chatName;
        this.lastActivity = LocalDateTime.now();
    }
    
    public List<String> getParticipantIds() {
        return new ArrayList<>(participantIds);
    }
    
    public LocalDateTime getCreatedAt() {
        return createdAt;
    }
    
    public LocalDateTime getLastActivity() {
        return lastActivity;
    }
    
    public ChatType getChatType() {
        return chatType;
    }
    
    @Override
    public String toString() {
        return String.format("Chat{id='%s', name='%s', type=%s, participants=%d, messages=%d}", 
                           chatId, chatName, chatType, participantIds.size(), messages.size());
    }
}