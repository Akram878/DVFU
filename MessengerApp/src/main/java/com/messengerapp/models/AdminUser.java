package com.messengerapp.models;

import java.util.List;
import java.util.ArrayList;

/**
 * AdminUser extends User to demonstrate inheritance.
 * Admin users have additional privileges like managing other users.
 */
public class AdminUser extends User {
    private List<String> permissions;
    private boolean canModerateChats;
    
    /**
     * Default constructor for AdminUser
     */
    public AdminUser() {
        super();
        this.permissions = new ArrayList<>();
        this.canModerateChats = true;
        initializeAdminPermissions();
    }
    
    /**
     * Constructor with name
     * @param name Admin user's name
     */
    public AdminUser(String name) {
        super(name);
        this.permissions = new ArrayList<>();
        this.canModerateChats = true;
        initializeAdminPermissions();
    }
    
    /**
     * Initialize default admin permissions
     */
    private void initializeAdminPermissions() {
        permissions.add("MANAGE_USERS");
        permissions.add("MODERATE_CHATS");
        permissions.add("VIEW_SYSTEM_LOGS");
        permissions.add("BROADCAST_MESSAGES");
    }
    
    /**
     * Add a permission to the admin user
     * @param permission The permission to add
     */
    public void addPermission(String permission) {
        if (!permissions.contains(permission)) {
            permissions.add(permission);
        }
    }
    
    /**
     * Remove a permission from the admin user
     * @param permission The permission to remove
     */
    public void removePermission(String permission) {
        permissions.remove(permission);
    }
    
    /**
     * Check if admin has a specific permission
     * @param permission The permission to check
     * @return true if admin has the permission
     */
    public boolean hasPermission(String permission) {
        return permissions.contains(permission);
    }
    
    /**
     * Get all permissions
     * @return List of permissions
     */
    public List<String> getPermissions() {
        return new ArrayList<>(permissions);
    }
    
    /**
     * Check if admin can moderate chats
     * @return true if can moderate
     */
    public boolean canModerateChats() {
        return canModerateChats;
    }
    
    /**
     * Set chat moderation capability
     * @param canModerateChats true to enable chat moderation
     */
    public void setCanModerateChats(boolean canModerateChats) {
        this.canModerateChats = canModerateChats;
    }
    
    /**
     * Admin-specific method to ban a user (demonstration of extended functionality)
     * @param userId The ID of the user to ban
     * @return true if ban was successful
     */
    public boolean banUser(String userId) {
        if (hasPermission("MANAGE_USERS")) {
            // In a real application, this would interact with a user management system
            System.out.println("Admin " + getName() + " banned user with ID: " + userId);
            return true;
        }
        return false;
    }
    
    /**
     * Override toString to include admin-specific information
     */
    @Override
    public String toString() {
        return String.format("AdminUser{id='%s', name='%s', status=%s, permissions=%d}", 
                           getId(), getName(), getStatus(), permissions.size());
    }
}