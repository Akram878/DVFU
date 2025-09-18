package com.messengerapp.models;

/**
 * FileMessage implementation of Message.
 * Represents a file attachment message.
 */
public class FileMessage extends Message {
    private String filePath;
    private String fileName;
    private long fileSize; // in bytes
    private String mimeType;
    
    /**
     * Constructor for FileMessage
     * @param senderId ID of the sender
     * @param receiverId ID of the receiver
     * @param filePath Path to the file
     */
    public FileMessage(String senderId, String receiverId, String filePath) {
        super(senderId, receiverId);
        this.filePath = filePath;
        this.fileName = extractFileNameFromPath(filePath);
        this.fileSize = 0;
        this.mimeType = determineMimeType(filePath);
    }
    
    /**
     * Constructor with file metadata
     * @param senderId ID of the sender
     * @param receiverId ID of the receiver
     * @param filePath Path to the file
     * @param fileName Name of the file
     * @param fileSize Size of the file in bytes
     */
    public FileMessage(String senderId, String receiverId, String filePath, String fileName, long fileSize) {
        super(senderId, receiverId);
        this.filePath = filePath;
        this.fileName = fileName;
        this.fileSize = fileSize;
        this.mimeType = determineMimeType(filePath);
    }
    
    @Override
    public String getContent() {
        return fileName + " (" + formatFileSize(fileSize) + ")";
    }
    
    @Override
    public String getMessageType() {
        return "FILE";
    }
    
    @Override
    public void displayMessage() {
        System.out.println("[" + getFormattedTimestamp() + "] File: " + fileName);
        System.out.println("    Path: " + filePath);
        if (fileSize > 0) {
            System.out.println("    Size: " + formatFileSize(fileSize));
        }
        if (mimeType != null && !mimeType.isEmpty()) {
            System.out.println("    Type: " + mimeType);
        }
    }
    
    /**
     * Extract filename from file path
     * @param path The file path
     * @return The filename
     */
    private String extractFileNameFromPath(String path) {
        if (path == null) return "unknown";
        int lastSeparator = Math.max(path.lastIndexOf('/'), path.lastIndexOf('\\'));
        return lastSeparator >= 0 ? path.substring(lastSeparator + 1) : path;
    }
    
    /**
     * Determine MIME type based on file extension
     * @param path The file path
     * @return The MIME type
     */
    private String determineMimeType(String path) {
        if (path == null || !path.contains(".")) {
            return "application/octet-stream";
        }
        
        String extension = path.substring(path.lastIndexOf(".") + 1).toLowerCase();
        switch (extension) {
            case "txt": return "text/plain";
            case "pdf": return "application/pdf";
            case "doc": case "docx": return "application/msword";
            case "xls": case "xlsx": return "application/vnd.ms-excel";
            case "ppt": case "pptx": return "application/vnd.ms-powerpoint";
            case "zip": return "application/zip";
            case "jpg": case "jpeg": return "image/jpeg";
            case "png": return "image/png";
            case "gif": return "image/gif";
            case "mp3": return "audio/mpeg";
            case "mp4": return "video/mp4";
            default: return "application/octet-stream";
        }
    }
    
    /**
     * Format file size for display
     * @param bytes File size in bytes
     * @return Formatted file size string
     */
    private String formatFileSize(long bytes) {
        if (bytes < 1024) return bytes + " B";
        if (bytes < 1024 * 1024) return String.format("%.1f KB", bytes / 1024.0);
        if (bytes < 1024 * 1024 * 1024) return String.format("%.1f MB", bytes / (1024.0 * 1024.0));
        return String.format("%.1f GB", bytes / (1024.0 * 1024.0 * 1024.0));
    }
    
    /**
     * Check if file is an image
     * @return true if file is an image
     */
    public boolean isImage() {
        return mimeType != null && mimeType.startsWith("image/");
    }
    
    /**
     * Check if file is a document
     * @return true if file is a document
     */
    public boolean isDocument() {
        return mimeType != null && (mimeType.contains("text") || 
               mimeType.contains("pdf") || mimeType.contains("msword") || 
               mimeType.contains("excel") || mimeType.contains("powerpoint"));
    }
    
    // Getters and Setters
    public String getFilePath() {
        return filePath;
    }
    
    public void setFilePath(String filePath) {
        this.filePath = filePath;
        this.fileName = extractFileNameFromPath(filePath);
        this.mimeType = determineMimeType(filePath);
    }
    
    public String getFileName() {
        return fileName;
    }
    
    public void setFileName(String fileName) {
        this.fileName = fileName;
    }
    
    public long getFileSize() {
        return fileSize;
    }
    
    public void setFileSize(long fileSize) {
        this.fileSize = fileSize;
    }
    
    public String getMimeType() {
        return mimeType;
    }
    
    public void setMimeType(String mimeType) {
        this.mimeType = mimeType;
    }
}