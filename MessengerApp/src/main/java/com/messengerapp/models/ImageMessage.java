package com.messengerapp.models;

/**
 * ImageMessage implementation of Message.
 * Represents an image message with file path and metadata.
 */
public class ImageMessage extends Message {
    private String imagePath;
    private String caption;
    private long fileSize; // in bytes
    private String format; // jpg, png, gif, etc.
    
    /**
     * Constructor for ImageMessage
     * @param senderId ID of the sender
     * @param receiverId ID of the receiver
     * @param imagePath Path to the image file
     */
    public ImageMessage(String senderId, String receiverId, String imagePath) {
        super(senderId, receiverId);
        this.imagePath = imagePath;
        this.caption = "";
        this.fileSize = 0;
        this.format = extractFormatFromPath(imagePath);
    }
    
    /**
     * Constructor with caption
     * @param senderId ID of the sender
     * @param receiverId ID of the receiver
     * @param imagePath Path to the image file
     * @param caption Caption for the image
     */
    public ImageMessage(String senderId, String receiverId, String imagePath, String caption) {
        this(senderId, receiverId, imagePath);
        this.caption = caption;
    }
    
    @Override
    public String getContent() {
        return imagePath + (caption.isEmpty() ? "" : " - " + caption);
    }
    
    @Override
    public String getMessageType() {
        return "IMAGE";
    }
    
    @Override
    public void displayMessage() {
        System.out.println("[" + getFormattedTimestamp() + "] Image: " + imagePath);
        if (!caption.isEmpty()) {
            System.out.println("    Caption: " + caption);
        }
        if (fileSize > 0) {
            System.out.println("    Size: " + formatFileSize(fileSize) + " | Format: " + format);
        }
    }
    
    /**
     * Extract file format from file path
     * @param path The file path
     * @return The file format/extension
     */
    private String extractFormatFromPath(String path) {
        if (path == null || !path.contains(".")) {
            return "unknown";
        }
        return path.substring(path.lastIndexOf(".") + 1).toLowerCase();
    }
    
    /**
     * Format file size for display
     * @param bytes File size in bytes
     * @return Formatted file size string
     */
    private String formatFileSize(long bytes) {
        if (bytes < 1024) return bytes + " B";
        if (bytes < 1024 * 1024) return String.format("%.1f KB", bytes / 1024.0);
        return String.format("%.1f MB", bytes / (1024.0 * 1024.0));
    }
    
    // Getters and Setters
    public String getImagePath() {
        return imagePath;
    }
    
    public void setImagePath(String imagePath) {
        this.imagePath = imagePath;
        this.format = extractFormatFromPath(imagePath);
    }
    
    public String getCaption() {
        return caption;
    }
    
    public void setCaption(String caption) {
        this.caption = caption;
    }
    
    public long getFileSize() {
        return fileSize;
    }
    
    public void setFileSize(long fileSize) {
        this.fileSize = fileSize;
    }
    
    public String getFormat() {
        return format;
    }
    
    public void setFormat(String format) {
        this.format = format;
    }
}