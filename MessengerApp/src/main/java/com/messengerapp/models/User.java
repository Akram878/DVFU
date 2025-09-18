package com.messengerapp.models;

import java.util.Objects;
import java.util.UUID;

/**
 * Represents a user in the messenger application.
 * Demonstrates encapsulation with private fields and public getters/setters.
 */
public class User {
    private String id;
    private String name;
    private UserStatus status;
    
    /**
     * Enum representing different user statuses
     */
    public enum UserStatus {
        ONLINE, OFFLINE, AWAY, BUSY
    }
    
    /**
     * Default constructor - creates user with OFFLINE status
     */
    public User() {
        this.id = UUID.randomUUID().toString();
        this.status = UserStatus.OFFLINE;
    }
    
    /**
     * Constructor with name parameter
     * @param name The user's name
     */
    public User(String name) {
        this();
        this.name = name;
    }
    
    /**
     * Full constructor
     * @param id Unique user identifier
     * @param name User's display name
     * @param status Current user status
     */
    public User(String id, String name, UserStatus status) {
        this.id = id;
        this.name = name;
        this.status = status;
    }
    
    // Getters and Setters (Encapsulation)
    public String getId() {
        return id;
    }
    
    public void setId(String id) {
        this.id = id;
    }
    
    public String getName() {
        return name;
    }
    
    public void setName(String name) {
        this.name = name;
    }
    
    public UserStatus getStatus() {
        return status;
    }
    
    public void setStatus(UserStatus status) {
        this.status = status;
    }
    
    /**
     * Updates user status to online
     */
    public void goOnline() {
        this.status = UserStatus.ONLINE;
    }
    
    /**
     * Updates user status to offline
     */
    public void goOffline() {
        this.status = UserStatus.OFFLINE;
    }
    
    /**
     * Checks if user is currently online
     * @return true if user status is ONLINE
     */
    public boolean isOnline() {
        return this.status == UserStatus.ONLINE;
    }
    
    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (obj == null || getClass() != obj.getClass()) return false;
        User user = (User) obj;
        return Objects.equals(id, user.id);
    }
    
    @Override
    public int hashCode() {
        return Objects.hash(id);
    }
    
    @Override
    public String toString() {
        return String.format("User{id='%s', name='%s', status=%s}", id, name, status);
    }
}